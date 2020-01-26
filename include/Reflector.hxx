#ifndef __REFLECTOR_HXX__
#define __REFLECTOR_HXX__

#include <map>

class Reflector
{
    private:
        std::map<char, char> _reflector_dict;
        const char _name;
    public:
        Reflector(const char name, const std::map<char, char> ref_dict) : 
            _name(name), _reflector_dict(ref_dict) {}
        const char reflector_conversion(const char letter){return _reflector_dict[letter];}
};

class Reflector_B : public Reflector
{
    public:
        Reflector_B() : Reflector('B',
			{{'A', 'Y'}, {'B', 'R'}, {'C', 'U'},
			{'D', 'H'}, {'E', 'Q'}, {'F', 'S'},
			{'G', 'L'}, {'H', 'D'}, {'K', 'N'},
			{'L', 'G'}, {'M', 'O'}, {'N', 'K'},
			{'O', 'M'}, {'P', 'I'}, {'Q', 'E'},
			{'R', 'B'}, {'S', 'F'}, {'T', 'Z'},
			{'U', 'C'}, {'V', 'W'}, {'W', 'V'},
			{'X', 'J'}, {'Y', 'A'}, {'Z', 'T'},
			{'I', 'P'}, {'J', 'X'}}) {}
};

class Reflector_C : public Reflector
{
    public:
        Reflector_C() : Reflector('C',
			{{ 'A', 'Y'}, {'B', 'R'}, {'C', 'U'},
			{'D', 'H'}, {'E', 'Q'}, {'F', 'S'},
			{'G', 'L'}, {'H', 'D'}, {'K', 'N'},
			{'L', 'G'}, {'M', 'O'}, {'N', 'K'},
			{'O', 'M'}, {'P', 'I'}, {'Q', 'E'},
			{'R', 'B'}, {'S', 'F'}, {'T', 'Z'},
			{'U', 'C'}, {'V', 'W'}, {'W', 'V'},
			{'X', 'J'}, {'Y', 'A'}, {'Z', 'T'},
			{'I', 'P'}, {'J', 'X'}}) {}
};

#endif
