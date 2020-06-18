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

typedef std::vector<std::string> RotorLabels;
typedef std::map<std::string, Rotor*> RotorMap;

class _enigma_impl
{
    public:
        _enigma_impl(const std::vector<int> rotor_list, const char reflector, const std::string enigma_type, const bool debug) :
            _rotor_ids(rotor_list), _reflector_type(reflector), _enigma_type(enigma_type), 
            _logger(Logger("ENIGMA "+enigma_type)), _debug(debug), _reflector(Reflectors(reflector))
        {
            _init();
        }
        const std::string _enigma_type;
        RotorLabels _rotor_labels;
        const std::vector<int> _rotor_ids;
        RotorMap _rotors;
        const char _reflector_type;
        Reflector* _reflector;
        Plugboard* _plugboard = new Plugboard;
        void _init();
        void _move_rotor(const std::string, const int);
        void _set_rotor(const std::string, const char);
        char _get_rotor_conv(const std::string, const char);
        char _get_rotor_conv_inv(const std::string, const char);
        char _get_inter_rotor_conv(const std::string, const std::string, const char);
        char _get_reflector_conv(const char);
        Logger _logger;
        bool _debug = false;
};

class Enigma
{
    private:
        _enigma_impl* _impl;
    public:
        Enigma(const std::vector<int> rotor_list={5,3,1}, const char reflector='B', const std::string enigma_type="M3", const bool debug=false) :
            _impl(new _enigma_impl(rotor_list, reflector, enigma_type, debug)) {}
        const int rotor_index(const std::string);
        void ringstellung(const std::string, const int);
        char type_letter(const char);
        std::string type_phrase(const std::string);
        void set_key(const std::string);
        void rewire_plugboard(const char, const char);
        void reset(){_impl->_init();}
        std::string getType() const {return _impl->_enigma_type;}
        std::vector<std::string> getRotorLabels() const {return static_cast<RotorLabels>(_impl->_rotor_labels);}
};

#endif