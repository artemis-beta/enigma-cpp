#ifndef __ENIGMA_HXX__
#define __ENIGMA_HXX__

#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <ranges>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Rotor.hxx"
#include "Plugboard.hxx"
#include "Reflector.hxx"
#include "spdlog/spdlog.h"

#ifndef VERSION
#error Macro VERSION must be defined
#endif

#ifndef BETA
#error Macro BETA must be defined
#endif

namespace EnigmaInfo
{
    const std::string version = std::string(VERSION);
    const bool isBeta = static_cast<bool>(BETA);
};

typedef std::vector<std::string> RotorLabels;
typedef std::map<std::string, Rotor*> RotorMap;

enum class EnigmaType
{
    M3,
    M4
};

class _enigma_impl
{
    public:
        const EnigmaType _enigma_type;
        RotorLabels _rotor_labels;
        const std::vector<int> _rotor_ids;
        RotorMap _rotors;
        const char _reflector_type;
        bool _debug = false;
        Reflector* _reflector;
        Plugboard* _plugboard = new Plugboard;

        _enigma_impl(const std::vector<int> rotor_list, const char reflector, const EnigmaType enigma_type, const bool debug) :
            _enigma_type(enigma_type), _rotor_ids(rotor_list), _reflector_type(reflector),
            _debug(debug), _reflector(Reflectors(reflector))
        {
            _init();
        }

        void _init();
        void _move_rotor(const std::string, const int);
        void _set_rotor(const std::string, const char);
        char _get_rotor_conv(const std::string, const char);
        char _get_rotor_conv_inv(const std::string, const char);
        char _get_inter_rotor_conv(const std::string, const std::string, const char);
        char _get_reflector_conv(const char);
};

class Enigma
{
    private:
        _enigma_impl* _impl;
    public:
        Enigma(const std::vector<int> rotor_list={5,3,1}, const char reflector='B', const EnigmaType enigma_type=EnigmaType::M3, const bool debug=false) :
            _impl(new _enigma_impl(rotor_list, reflector, enigma_type, debug)) {}
        int rotor_index(const std::string&) const;
        void ringstellung(const std::string, const int);
        char type_letter(const char);
        std::string type_phrase(const std::string);
        void set_key(const std::string);
        void rewire_plugboard(const char, const char);
        void reset(){_impl->_init();}
        EnigmaType getType() const {return _impl->_enigma_type;}
        std::vector<std::string> getRotorLabels() const {return static_cast<RotorLabels>(_impl->_rotor_labels);}
};

#endif
