#include "Rotor.hxx"

const int Rotor::alpha_index(const char letter)
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

const int Rotor::get_output_terminal(const char letter)
{
	const int i = alpha_index(letter);
	return _wiring[i];
}

const int Rotor::get_input_terminal(const char letter)
{
	const int i = alpha_index(letter);
	for(unsigned int j{0}; j < _wiring.size(); ++j)
	{
		if(i == j)
		{
			return i;
		}
	}

	throw std::invalid_argument("Could not find Input terminal for letter '"+std::to_string(letter)+"'");
}

const char Rotor::get_rotor_conversion(const char letter)
{
	const int i = alpha_index(letter);

	return _alpha[_wiring[i]];
}

const char Rotor::get_rotor_conversion_inv(const char letter)
{
	const int i = alpha_index(letter);

	for(unsigned int j{0}; j < _wiring.size(); ++j)
	{
		if(_wiring[j] == i)
		{
			return _alpha[j];
		}
	}

	throw std::invalid_argument("Could not find the inverse of character '"+std::to_string(letter)+"'");
}

