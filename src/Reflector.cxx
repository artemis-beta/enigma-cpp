#include "Reflector.hxx"

extern Reflector* Reflectors(const char type)
{
	if(type != 'B' && type != 'C')
	{
		throw std::invalid_argument("Could not find Reflector of type '"+std::string(1, type)+"'");
	}

	if(type == 'B')
	{
		return new Reflector_B;
	}
	else
	{
		return new Reflector_C;
	}
}