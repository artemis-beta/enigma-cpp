#ifndef __ROTOR_HXX__
#define __ROTOR_HXX__

#include <array>
#include <vector>
#include <map>
#include <stdexcept>
#include <string>

class Rotor
{
    private:
        const std::array<const char, 26> _alpha = {'A', 'B', 'C', 'D', 'E', 'F',
                                                'G', 'H', 'I', 'J', 'K', 'L',
                                                'M', 'N', 'O', 'P', 'Q', 'R',
                                                'S', 'T', 'U', 'V', 'W', 'X',
                                                'Y', 'Z'};
        const std::vector<char> _notches;
        char _face = 'A';
        const std::string _name;
        std::map<int,int> _wiring;
    public:
        Rotor(const std::string name, const std::vector<char> notches, std::map<int, int> wiring) : 
            _notches(notches), _name(name) {}
        void rotate_rotor(Rotor* other=nullptr);
        void rotate_inner_ring();
        const int get_output_terminal(const char letter);
        const int get_input_terminal(const char letter);
        const char get_rotor_conversion(const char letter);
        const char get_rotor_conversion_inv(const char letter);
		const char get_face_letter(){return _face;}
		const std::vector<char> get_notches(){return _notches;}
		const std::array<const char, 26> get_letters_dict(){return _alpha;}
		const int alpha_index(const char letter);
};

class Rotor_1 : public Rotor
{
    public:
        Rotor_1() : Rotor("I", {'R'}, 
			{{0, 4}, {1, 10}, {2, 12},
			{3, 5}, {4, 11}, {5, 6},
			{6, 3}, {7, 16}, {8, 21},
			{9, 25}, {10, 13}, {11, 19},
			{12, 14}, {13, 22}, {14, 24},
			{15, 7}, {16, 23}, {17, 20},
			{18, 18}, {19, 15}, {20, 0},
			{21, 8}, {22, 1}, {23, 17},
			{24, 2}, {25, 9}}) {}
};

class Rotor_2 : public Rotor
{
    public:
        Rotor_2() : Rotor("II", {'F'}, 
			{{0, 0}, {1, 9}, {2, 3},
			{3, 10}, {4, 18}, {5, 8},
			{6, 17}, {7, 20}, {8, 23},
			{9, 1}, {10, 11}, {11, 7},
			{12, 22}, {13, 19}, {14, 12},
			{15, 2}, {16, 16}, {17, 6},
			{18, 25}, {19, 13}, {20, 15},
			{21, 24}, {22, 5}, {23, 21},
			{24, 14}, {25, 4}}) {}
};

class Rotor_3 : public Rotor
{
    public:
		Rotor_3() : Rotor("III", {'W'},
			{{0, 1}, {1, 3}, {2, 5},
			{3, 7}, {4, 9}, {5, 11},
			{6, 2}, {7, 15}, {8, 17},
			{9, 19}, {10, 23}, {11, 21},
			{12, 25}, {13, 13}, {14, 24},
			{15, 4}, {16, 8}, {17, 22},
			{18, 6}, {19, 0}, {20, 10},
			{21, 12}, {22, 20}, {23, 18},
			{24, 16}, {25, 14}}) {}
};

class Rotor_4 : public Rotor
{
    public:
		Rotor_4() : Rotor("IV", {'K'},
			{{0, 4}, {1, 18}, {2, 14},
			{3, 21}, {4, 15}, {5, 25},
			{6, 9}, {7, 0}, {8, 24},
			{9, 16}, {10, 20}, {11, 8},
			{12, 17}, {13, 7}, {14, 23},
			{15, 11}, {16, 13}, {17, 5},
			{18, 19}, {19, 6}, {20, 10},
			{21, 3}, {22, 2}, {23, 12},
			{24, 22}, {25, 1}}) {}
};

class Rotor_5 : public Rotor
{
	public:
		Rotor_5() : Rotor("V", {'A'},
				{{0, 21}, {1, 25}, {2, 1},
				{3, 17}, {4, 6}, {5, 8},
				{6, 19}, {7, 24}, {8, 20},
				{9, 15}, {10, 18}, {11, 3},
				{12, 13}, {13, 7}, {14, 11},
				{15, 23}, {16, 0}, {17, 22},
				{18, 12}, {19, 9}, {20, 16},
				{21, 14}, {22, 5}, {23, 4},
				{24, 2}, {25, 10}}) {}
};

class Rotor_6 : public Rotor
{
	public:
		Rotor_6() : Rotor("VI", {'A', 'N'},
				{{0, 9}, {1, 15}, {2, 6},
				{3, 21}, {4, 14}, {5, 20},
				{6, 12}, {7, 5}, {8, 24},
				{9, 16}, {10, 1}, {11, 4},
				{12, 13}, {13, 7}, {14, 25},
				{15, 17}, {16, 3}, {17, 10},
				{18, 0}, {19, 18}, {20, 23},
				{21, 11}, {22, 8}, {23, 2},
				{24, 19}, {25, 22}}) {}
};

class Rotor_7 : public Rotor
{
	public:
		Rotor_7() : Rotor("VII", {'A', 'N'},
				{{0, 13}, {1, 25}, {2, 9},
				{3, 7}, {4, 6}, {5, 17},
				{6, 2}, {7, 23}, {8, 12},
				{9, 24}, {10, 18}, {11, 22},
				{12, 1}, {13, 14}, {14, 20},
				{15, 5}, {16, 0}, {17, 8},
				{18, 21}, {19, 11}, {20, 15},
				{21, 4}, {22, 10}, {23, 16},
				{24, 3}, {25, 19}}) {}
};


class Rotor_8 : public Rotor
{
	public:
		Rotor_8() : Rotor("VIII", {'A', 'N'},
				{{0, 5}, {1, 10}, {2, 16},
				{3, 7}, {4, 19}, {5, 11},
				{6, 23}, {7, 14}, {8, 2},
				{9, 1}, {10, 9}, {11, 18},
				{12, 15}, {13, 3}, {14, 25},
				{15, 17}, {16, 0}, {17, 12},
				{18, 4}, {19, 22}, {20, 13},
				{21, 8}, {22, 20}, {23, 24},
				{24, 6}, {25, 21}}) {}
};

Rotor* Rotors(const int rotor_type)
{
    if(rotor_type > 8 || rotor_type < 1)
    {
        throw std::invalid_argument("Could not find Rotor of type '"+std::to_string(rotor_type)+"'");
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

#endif
