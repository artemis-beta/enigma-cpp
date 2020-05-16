#ifndef __PLUGBOARD_HXX__
#define __PLUGBOARD_HXX__

#include <map>
#include <string>

class Plugboard
{
    private:
        std::map<char, char> _plug_board_dict = {{ 'A', 'Z'}, {'B', 'P'}, {'C', 'M'},
				{'D', 'S'}, {'E', 'Y'}, {'F', 'U'},
				{'G', 'N'}, {'H', 'V'}, {'I', 'Q'},
				{'J', 'X'}, {'K', 'T'}, {'L', 'R'},
				{'M', 'C'}, {'N', 'G'}, {'O', 'W'},
				{'P', 'B'}, {'Q', 'I'}, {'R', 'L'},
				{'S', 'D'}, {'T', 'K'}, {'U', 'F'},
				{'V', 'H'}, {'W', 'O'}, {'X', 'J'},
				{'Y', 'E'}, {'Z', 'A'}};
    public:
        char plugboard_conversion(const char letter)
        {
            return _plug_board_dict[letter];
        }

        char plugboard_conversion_inv(const char letter)
        {
            for(auto key : _plug_board_dict)
            {
                if(key.second == letter)
                {
                    return key.first;
                }
            }

            throw std::invalid_argument("Could find inverse conversion of character '"+std::string(1, letter)+"'");
        }

        void swap_letter_wiring(const char letter_1, const char letter_2)
        {
            const char init_1 = plugboard_conversion(letter_1);
            const char init_2 = plugboard_conversion_inv(letter_2);
            _plug_board_dict[letter_1] = letter_2;
            _plug_board_dict[letter_2] = letter_1;
            _plug_board_dict[init_2] = init_1;
            _plug_board_dict[init_1] = init_2;
        }
};

#endif
