#include "Enigma.hxx"

const int Enigma::rotor_index(const std::string label)
{
	const std::vector<std::string>::iterator it = std::find(_rotor_labels.begin(), _rotor_labels.end(), label);
	return std::distance(_rotor_labels.begin(), it);
}

void Enigma::send_message_to_QDebug(const QString& msg_type, const QString& message)
{
    if(_debug)
    {
        qDebug() << msg_type << ": " << message << "\n";
    }
}

void Enigma::_init()
{
    srand(time(NULL));

    if(_enigma_type == "M3")
    {
        _rotor_labels = {"left", "middle", "right"};
        if(_rotor_ids.size() != 3)
        {
            send_message_to_QDebug("ERROR", "Three rotor types only must be provided for Enigma machine 'M3'");
            exit(EXIT_FAILURE);
        }

        std::vector<int> _temp = _rotor_ids;
        
        const std::vector<int>::iterator it = std::unique(_temp.begin(), _temp.end());

        if(std::distance(_temp.begin(), it) != 3)
        {
            send_message_to_QDebug("ERROR", "All chosen rotor IDs must be unique");
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
            send_message_to_QDebug("ERROR", "Four rotor types only must be provided for Enigma machine 'M4'");
            exit(EXIT_FAILURE);
        }

        _rotor_labels = {"left", "middle left", "middle right", "right"};
        
        std::vector<int> _temp = _rotor_ids;
        const std::vector<int>::iterator it = std::unique(_temp.begin(), _temp.end());

        if(std::distance(_temp.begin(), it) != 4)
        {
            send_message_to_QDebug("ERROR", "All chosen rotor IDs must be unique");
            exit(EXIT_FAILURE);
        }
        _rotors[_rotor_labels[0]] = Rotors(_rotor_ids[0]);
        _rotors[_rotor_labels[1]] = Rotors(_rotor_ids[1]);
        _rotors[_rotor_labels[2]] = Rotors(_rotor_ids[2]);
        _rotors[_rotor_labels[3]] = Rotors(_rotor_ids[3]);
    }

    else
    {
        send_message_to_QDebug("ERROR", QString("Unrecognised Enigma type '%1'").arg(QString::fromUtf8(_enigma_type.c_str())));
        exit(EXIT_FAILURE);
    }
}

void Enigma::_move_rotor(const std::string rotor, const int amount)
{
    send_message_to_QDebug("DEBUG", QString("Rotating rotor %1 by %2").arg(QString::fromUtf8(rotor.c_str()), amount));
    for(unsigned int i{0}; i < amount; ++i)
    {
        _rotors[rotor]->rotate_rotor();
    }
}

void Enigma::ringstellung(const std::string name, const int amount)
{
    for(unsigned int i{0}; i < amount; ++i)
    {
        char letter = 'A';
        send_message_to_QDebug("DEBUG", QString("Ringstellung: Conversion for rotor %1 was %2 to %3").arg(
                    QString::fromUtf8(name.c_str()), QString(letter), QString(_rotors[name]->get_rotor_conversion(letter))));
        _rotors[name]->rotate_inner_ring();
        send_message_to_QDebug("DEBUG", QString("Ringstellung: Conversion for rotor %1 was %2 to %3").arg(
                    QString::fromUtf8(name.c_str()), QString(letter), QString(_rotors[name]->get_rotor_conversion(letter))));
    }
}

void Enigma::_set_rotor(const std::string name, const char letter)
{
    send_message_to_QDebug("DEBUG", QString("Setting rotor %1 to %2").arg(QString::fromUtf8(name.c_str()), QString(letter)));
    
    while(_rotors[name]->get_face_letter() != letter)
    {
        _move_rotor(name, 1);
    }
}

const char Enigma::_get_rotor_conv(const std::string name, const char letter)
{
    const char converted_letter = _rotors[name]->get_rotor_conversion(letter);
    send_message_to_QDebug("DEBUG", QString("Rotor %1 conversion: %2 to %3").arg(QString::fromUtf8(name.c_str()), QString(letter), QString(converted_letter)));
    return converted_letter;
}

const char Enigma::_get_rotor_conv_inv(const std::string name, const char letter)
{
    const char converted_letter = _rotors[name]->get_rotor_conversion_inv(letter);
    send_message_to_QDebug("DEBUG", QString("Rotor %1 conversion: %2 to %3").arg(QString::fromUtf8(name.c_str()), QString(letter), QString(converted_letter)));
    return converted_letter;
}

const char Enigma::_get_inter_rotor_conv(const std::string name_1,
                                         const std::string name_2,
                                         const char letter)
{
    const int terminal = _rotors[name_1]->alpha_index(letter);
    const int zero_point_1 = _rotors[name_1]->alpha_index(_rotors[name_1]->get_face_letter());
    const int zero_point_2 = _rotors[name_2]->alpha_index(_rotors[name_2]->get_face_letter());
    const int interval = zero_point_2 - zero_point_1;

    int n = 0;

    if(interval > 0)
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

    send_message_to_QDebug("DEBUG", QString("Rotor %1 rotor to %2 rotor conversion: %3 to %4").arg(QString::fromUtf8(name_1.c_str()),
                                                                                                   QString::fromUtf8(name_2.c_str()),
                                                                                                   QString(letter), QString(output)));


    return output;
}

const char Enigma::_get_inter_rotor_conv_inv(const std::string name_1,
                                             const std::string name_2,
                                             const char letter)
{
    return _get_inter_rotor_conv(name_1, name_2, letter);
}

const char Enigma::type_letter(const char letter)
{
    const char l  = std::toupper(letter);
    send_message_to_QDebug("DEBUG","-----------------------");
    char cipher = _plugboard->plugboard_conversion(l);
    send_message_to_QDebug("DEBUG", QString("Plugboard conversion: %1 to %2").arg(QString(l), QString(cipher)));
    // Move the rightmost rotor
    
    _move_rotor(_rotor_labels[_rotor_labels.size()-1], 1);
    
    std::vector<std::string> reversed = _rotor_labels;
    
    std::vector<std::string> reversed_1 = _rotor_labels;
    
    reversed_1.erase(reversed_1.begin());
    
    std::vector<std::string> reversed_2 = _rotor_labels;
    
    reversed_2.pop_back();
    
    std::reverse(reversed.begin(), reversed.end());
    
    std::reverse(reversed_1.begin(), reversed_1.end());
    
    std::reverse(reversed_2.begin(), reversed_2.end());
    
    for(unsigned int i{0}; i < reversed_1.size(); ++i)
    {
        const std::string rev_1_element = reversed_1[i];
        const std::string rev_2_element = reversed_2[i];
        for(auto notch : _rotors[rev_1_element]->get_notches())
        {
            if(_rotors[rev_1_element]->get_face_letter() == notch)
            {
                _move_rotor(rev_2_element, 1);
            }
        }
    }

    // Encoding passing through enigma forwards
    for(auto key : reversed)
    {
        cipher = _get_rotor_conv(key, cipher);
        int adjacent_rotor_index = rotor_index(key)-1;

        if(adjacent_rotor_index < 0) break;

        const std::string adjacent_rotor= _rotor_labels[adjacent_rotor_index];

        cipher = _get_inter_rotor_conv(key, adjacent_rotor, cipher);

    }

    cipher = _get_reflector_conv(cipher);

    // Encoding propagating result backwards
    for(auto key : _rotor_labels)
    {
        cipher = _get_rotor_conv_inv(key, cipher);
        int adjacent_rotor_index = rotor_index(key)+1;

        if(adjacent_rotor_index >= _rotor_labels.size()) break;

        const std::string adjacent_rotor= _rotor_labels[adjacent_rotor_index];

        cipher = _get_inter_rotor_conv_inv(key, adjacent_rotor, cipher);
    }

    const char cipher_out = _plugboard->plugboard_conversion_inv(cipher);
    send_message_to_QDebug("DEBUG", QString("Plugboard conversion: %1 to %2").arg(QString(cipher), QString(cipher_out)));
    send_message_to_QDebug("DEBUG", "-----------------------");

    return cipher_out;
}

const char Enigma::_get_reflector_conv(const char letter)
{
    const char out = _reflector->reflector_conversion(letter);
    send_message_to_QDebug("DEBUG", QString("Reflector conversion: %1 to %2").arg(QString(letter), QString(out)));
    return out;
}

const std::string Enigma::type_phrase(const std::string phrase)
{
    std::string _temp = phrase;
    _temp.erase(std::remove_if(_temp.begin(), _temp.end(), ::isspace), _temp.end());
    const int remainder = (_temp.size() % 5 != 0) ? 5 - _temp.size() % 5 : 0;
    for(unsigned int i{0}; i < remainder; ++i)
    {
        _temp += _rotors[_rotor_labels[0]]->get_letters_dict()[rand() % 26];
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

    if(_rotor_labels.size() != key.size())
    {
        throw std::invalid_argument("Key length must match no. of rotors.");
    }
    
    boost::to_upper(key);

    for(unsigned int i{0}; i < _rotor_labels.size(); ++i)
    {
        _set_rotor(_rotor_labels[i], key[i]);
    }

}

void Enigma::rewire_plugboard(const char letter_1, const char letter_2)
{
    _plugboard->swap_letter_wiring(letter_1, letter_2);
}
