#include "Enigma.hxx"

int Enigma::rotor_index(const std::string label) const
{
	RotorLabels::iterator it = std::find(_impl->_rotor_labels.begin(), _impl->_rotor_labels.end(), label);
	if(it == _impl->_rotor_labels.end())
	{
		 _impl->_logger.Critical("Could not find Rotor, '"+label+"' in rotor list");
			
		 std::string rotor_list = " ";

		 for(auto& label : _impl->_rotor_labels)
	         {
			 rotor_list += label+" ";
	         }

		 _impl->_logger.Critical("Rotor List is [%1%]", rotor_list);
	}
	return std::distance(_impl->_rotor_labels.begin(), it);
}

void _enigma_impl::_init()
{
    srand(time(NULL));

    setLoggerLevel( (_debug) ? "DEBUG" : "INFO" );

    if(_enigma_type == "M3")
    {
        _rotor_labels = {"left", "middle", "right"};
        if(_rotor_ids.size() != 3)
        {
            _logger.Error("Three rotor types only must be provided for Enigma machine 'M3'");
            exit(EXIT_FAILURE);
        }

        std::vector<int> _temp = _rotor_ids;
        
        const std::vector<int>::iterator it = std::unique(_temp.begin(), _temp.end());

        if(std::distance(_temp.begin(), it) != 3)
        {
            _logger.Error("All chosen rotor IDs must be unique");
            exit(EXIT_FAILURE);
        }
        
        _rotors[_rotor_labels[0]] = Rotors(_rotor_ids[0]);
        _rotors[_rotor_labels[1]] = Rotors(_rotor_ids[1]);
        _rotors[_rotor_labels[2]] = Rotors(_rotor_ids[2]);
    }

    else if(_enigma_type == "M4")
    {
        if(_rotor_ids.size() != 4)
        {
            _logger.Error("Four rotor types only must be provided for Enigma machine 'M4'");
            exit(EXIT_FAILURE);
        }

        _rotor_labels = {"left", "middle left", "middle right", "right"};
        
        std::vector<int> _temp = _rotor_ids;
        const std::vector<int>::iterator it = std::unique(_temp.begin(), _temp.end());

        if(std::distance(_temp.begin(), it) != 4)
        {
            _logger.Error("All chosen rotor IDs must be unique");
            exit(EXIT_FAILURE);
        }
        _rotors[_rotor_labels[0]] = Rotors(_rotor_ids[0]);
        _rotors[_rotor_labels[1]] = Rotors(_rotor_ids[1]);
        _rotors[_rotor_labels[2]] = Rotors(_rotor_ids[2]);
        _rotors[_rotor_labels[3]] = Rotors(_rotor_ids[3]);
    }

    else
    {
        _logger.Error("Unrecognised Enigma type '%1%'", _enigma_type);
        exit(EXIT_FAILURE);
    }
}

void _enigma_impl::_move_rotor(const std::string rotor, const int amount)
{
    _logger.Debug("Rotating rotor %1% by %2%", rotor, std::to_string(amount));
    for(int i{0}; i < amount; ++i)
    {
        _rotors[rotor]->rotate_rotor();
    }
}

void Enigma::ringstellung(const std::string name, const int amount)
{
    RotorMap rotors = static_cast<RotorMap>(_impl->_rotors);
    Logger logger = static_cast<Logger>(_impl->_logger);
    for(int i{0}; i < amount; ++i)
    {
        char letter = 'A';
        logger.Debug("Ringstellung: Conversion for rotor %1% was %2% to %3%", 
                    name, std::string(1, letter), 
                    std::string(1, rotors[name]->get_rotor_conversion(letter)));
        rotors[name]->rotate_inner_ring();
        logger.Debug("Ringstellung: Conversion for rotor %1% now %2% to %3%", 
                    name, std::string(1, letter), 
                    std::string(1, rotors[name]->get_rotor_conversion(letter)));
    }
}

void _enigma_impl::_set_rotor(const std::string name, const char letter)
{
    _logger.Debug("Setting rotor %1% to %2%", name, std::string(1, letter));
    
    while(_rotors[name]->get_face_letter() != letter)
    {
        _move_rotor(name, 1);
    }
}

char _enigma_impl::_get_rotor_conv(const std::string name, const char letter)
{
    const char converted_letter = _rotors[name]->get_rotor_conversion(letter);
    _logger.Debug("Rotor %1% conversion: %2% to %3%", name, std::string(1, letter),
                    std::string(1, converted_letter));
    return converted_letter;
}

char _enigma_impl::_get_rotor_conv_inv(const std::string name, const char letter)
{
    const char converted_letter = _rotors[name]->get_rotor_conversion_inv(letter);
    _logger.Debug("Rotor %1% conversion: %2% to %3%", name, std::string(1, letter),
                    std::string(1, converted_letter));
    return converted_letter;
}

char _enigma_impl::_get_inter_rotor_conv(const std::string name_1,
                                         const std::string name_2,
                                         const char letter)
{
    const int terminal = _rotors[name_1]->alpha_index(letter);
    const int zero_point_1 = _rotors[name_1]->alpha_index(_rotors[name_1]->get_face_letter());
    const int zero_point_2 = _rotors[name_2]->alpha_index(_rotors[name_2]->get_face_letter());
    const int interval = zero_point_2 - zero_point_1;

    int n = 0;

    if(zero_point_2 > zero_point_1)
    {
        const std::vector<int> i = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
                                    14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
        n = i[(terminal+interval) % i.size()];
    }
    else
    {
        const std::vector<int> i = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
                                    14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
        n = i[(26+terminal+interval) % i.size()];
    }
    
    const char output = _rotors[name_2]->get_letters_dict()[n];

    _logger.Debug("Rotor %1% rotor to %2% rotor conversion: %3% to %4%",
                    name_1, name_2, std::string(1, letter),
                    std::string(1, output));

    return output;
}

char Enigma::type_letter(const char letter)
{
    const char l  = std::toupper(letter);
    Logger logger = static_cast<Logger>(_impl->_logger);
    const RotorLabels rotor_labels = static_cast<RotorLabels>(_impl->_rotor_labels);
    RotorMap rotors = static_cast<RotorMap>(_impl->_rotors);
    logger.Debug("-----------------------");
    Plugboard* plug_board = static_cast<Plugboard*>(_impl->_plugboard);
    char cipher = plug_board->plugboard_conversion(l);
    logger.Debug("Plugboard conversion: %1% to %2%", std::string(1, l), std::string(1, cipher));
    // Move the rightmost rotor
    
    _impl->_move_rotor(rotor_labels[rotor_labels.size()-1], 1);
    
    std::vector<std::string> reversed = rotor_labels;
    
    std::vector<std::string> reversed_1 = rotor_labels;
    
    reversed_1.erase(reversed_1.begin());
    
    std::vector<std::string> reversed_2 = rotor_labels;
    
    reversed_2.pop_back();
    
    std::reverse(reversed.begin(), reversed.end());
    
    std::reverse(reversed_1.begin(), reversed_1.end());
    
    std::reverse(reversed_2.begin(), reversed_2.end());
    
    for(unsigned int i{0}; i < reversed_1.size(); ++i)
    {
        const std::string rev_1_element = reversed_1[i];
        const std::string rev_2_element = reversed_2[i];
        for(auto notch : rotors[rev_1_element]->get_notches())
        {
            if(rotors[rev_1_element]->get_face_letter() == notch)
            {
                _impl->_move_rotor(rev_2_element, 1);
            }
        }
    }

    // Encoding passing through enigma forwards
    for(auto key : reversed)
    {
        cipher = _impl->_get_rotor_conv(key, cipher);
        int adjacent_rotor_index = rotor_index(key)-1;

        if(adjacent_rotor_index < 0) break;

        const std::string adjacent_rotor= rotor_labels[adjacent_rotor_index];

        cipher = _impl->_get_inter_rotor_conv(key, adjacent_rotor, cipher);
    }

    cipher = _impl->_get_reflector_conv(cipher);

    // Encoding propagating result backwards
    for(auto key : rotor_labels)
    {
        cipher = _impl->_get_rotor_conv_inv(key, cipher);
        size_t adjacent_rotor_index = rotor_index(key)+1;

        if(adjacent_rotor_index >= rotor_labels.size()) break;

        const std::string adjacent_rotor= rotor_labels[adjacent_rotor_index];

        cipher = _impl->_get_inter_rotor_conv(key, adjacent_rotor, cipher);
    }

    const char cipher_out = plug_board->plugboard_conversion_inv(cipher);
    logger.Debug("Plugboard conversion: %1% to %2%", std::string(1, cipher), std::string(1, cipher_out));
    logger.Debug("-----------------------");

    return cipher_out;
}

char _enigma_impl::_get_reflector_conv(const char letter)
{
    const char out = _reflector->reflector_conversion(letter);
    _logger.Debug("Reflector conversion: %1% to %2%", std::string(1, letter), std::string(1, out));
    return out;
}

std::string Enigma::type_phrase(const std::string phrase)
{
    std::string _temp = phrase;
    
    RotorMap rotors = static_cast<RotorMap>(_impl->_rotors);
    
    const RotorLabels rotor_labels = static_cast<RotorLabels>(_impl->_rotor_labels);
    
    _temp.erase(std::remove_if(_temp.begin(), _temp.end(), ::isspace), _temp.end());
    
    const size_t remainder = (_temp.size() % 5 != 0) ? 5 - _temp.size() % 5 : 0;
    
    for(unsigned int i{0}; i < remainder; ++i)
    {
        _temp += rotors[rotor_labels[0]]->get_letters_dict()[rand() % 26];
    }

    std::string out_str = "";

    for( unsigned int i{0}; i < _temp.size(); ++i )
    {
        out_str += std::string(1, type_letter(_temp[i]));
        if((i+1) % 5 == 0) out_str += " ";
    }

    return out_str;   
}

void Enigma::set_key(const std::string user_key)
{
    std::string key = user_key;

    const RotorLabels rotor_labels = static_cast<RotorLabels>(_impl->_rotor_labels);

    if(rotor_labels.size() != key.size())
    {
        throw std::invalid_argument("Key length must match no. of rotors.");
    }
    
    boost::to_upper(key);

    for(unsigned int i{0}; i < rotor_labels.size(); ++i)
    {
        _impl->_set_rotor(rotor_labels[i], key[i]);
    }
}

void Enigma::rewire_plugboard(const char letter_1, const char letter_2)
{
    Plugboard* plug_board = static_cast<Plugboard*>(_impl->_plugboard);
    plug_board->swap_letter_wiring(letter_1, letter_2);
}
