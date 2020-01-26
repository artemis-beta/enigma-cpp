#ifndef __ENIGMA_HXX__
#define __ENIGMA_HXX__

#include <string>
#include <vector>

const std::string version = "v1.2.0";
const bool isBeta = true;

class Enigma
{
    private:
        const std::string _enigma_type;
        const std::vector<int> _rotor_ids;
        const char _reflector_type;

};

#endif