#include "Rotor.hxx"

int Rotor::alpha_index(const char letter) const
{
	const std::array<const char, 26>::iterator it = std::find(_alpha.begin(), _alpha.end(), letter);
	return std::distance(_alpha.begin(), it);
}

void Rotor::rotate_rotor(Rotor* other)
{
	int pos = alpha_index(_face);
	pos = (pos > 25) ? 0 : pos+1;

	if(other)
	{
		other->rotate_rotor();
	}

	_face = _alpha[pos];
}

//RINGSTELLUNG
void Rotor::rotate_inner_ring()
{
	int x = _wiring[0];
	for(unsigned int i{0}; i < _wiring.size(); ++i)
	{
		if( i == 25 ){_wiring[i] = x;}
		else
		{
			const int y = _wiring[i+1];
			_wiring[i] = y;
		}
	}
}

int Rotor::get_output_terminal(const char letter) const
{
	const int i = alpha_index(letter);
	return _wiring.at(i);
}

int Rotor::get_input_terminal(const char letter) const
{
	const int i = alpha_index(letter);
	for(unsigned int j{0}; j < _wiring.size(); ++j)
	{
		if(i == j)
		{
			return i;
		}
	}

	throw std::invalid_argument("Could not find Input terminal for letter '"+std::string(1, letter)+"'");
}

char Rotor::get_rotor_conversion(const char letter) const
{
	const int i = alpha_index(letter);

	return _alpha[_wiring.at(i)];
}

char Rotor::get_rotor_conversion_inv(const char letter) const
{
	const int i = alpha_index(letter);

	for(unsigned int j{0}; j < _wiring.size(); ++j)
	{
		if(_wiring.at(j) == i)
		{
			return _alpha[j];
		}
	}

	throw std::invalid_argument("Could not find the inverse of character '"+std::string(1, letter)+"'");
}

extern Rotor* Rotors(const int rotor_type)
{
    if(rotor_type > 8 || rotor_type < 1)
    {
        throw std::invalid_argument("Could not find Rotor of type '"+std::string(1, rotor_type)+"'");
    }
    Rotor* _temp;
    switch(rotor_type)
    {
        case 2:
            _temp = new Rotor_2();
            break;
        case 3:
            _temp = new Rotor_3();
            break;
        case 4:
            _temp = new Rotor_4();
            break;
        case 5:
            _temp = new Rotor_4();
            break;
        case 6:
            _temp = new Rotor_4();
            break;
        case 7:
            _temp = new Rotor_4();
            break;
        case 8:
            _temp = new Rotor_4();
            break;
        default:
            _temp = new Rotor_1();
    }

    return _temp;
}
