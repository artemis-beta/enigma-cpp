#ifndef __ENIGMA_HXX__
#define __ENIGMA_HXX__

#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "boost/algorithm/string.hpp"

#include "Rotor.hxx"
#include "Plugboard.hxx"
#include "Reflector.hxx"
#include "Logger.hxx"

namespace EnigmaInfo
{
    const std::string version = "v1.2.0";
    const bool isBeta = true;
};

class Enigma
{
    private:
        const std::string _enigma_type;
        std::vector<std::string> _rotor_labels;
        const std::vector<int> _rotor_ids;
        std::map<std::string, Rotor*> _rotors;
        const char _reflector_type;
        Reflector* _reflector;
        Plugboard* _plugboard = new Plugboard;
        void _init();
        void _move_rotor(const std::string, const int);
        void _set_rotor(const std::string, const char);
        const char _get_rotor_conv(const std::string, const char);
        const char _get_rotor_conv_inv(const std::string, const char);
        const char _get_inter_rotor_conv(const std::string, const std::string, const char);
        const char _get_inter_rotor_conv_inv(const std::string, const std::string, const char);
        const char _get_reflector_conv(const char);
        Logger _logger;
        bool _debug = false;
    public:
        Enigma(const std::vector<int> rotor_list={5,3,1}, const char reflector='B', const std::string enigma_type="M3", const bool debug=false) :
            _rotor_ids(rotor_list), _reflector_type(reflector), _enigma_type(enigma_type), 
            _logger(Logger("ENIGMA "+enigma_type)), _debug(debug), _reflector(Reflectors(reflector))
        {
            _init();
        }
        const int rotor_index(const std::string);
        void ringstellung(const std::string, const int);
        const char type_letter(const char);
        const std::string type_phrase(const std::string);
        void set_key(const std::string);
        void rewire_plugboard(const char, const char);
        void reset(){_init();}
};

#endif