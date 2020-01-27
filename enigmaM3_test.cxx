#include <iostream>
#include <string>

#include "Enigma.hxx"

int main(int argc, char** argv)
{
    Enigma* enigma_m3 = new Enigma;
    std::string eg_version = EnigmaInfo::version;

    if(EnigmaInfo::isBeta)
    {
        eg_version += " (BETA)";
    }

    std::string intro = "===========================================\n\n"
    "  WELCOME TO THE PYTHON ENIGMA M3 ENCODER\n"
    "                  "+eg_version;
    intro += "\n           Kristian Zarebski\n\n"
    "===========================================\n"
    "Type 'quit' to exit.\n\n";

    std::cout << intro;

    char input[100] = {0};

    while(!(std::strncmp(input, "quit", 4) == 0))
    {
        enigma_m3 = new Enigma({5,3,1}, 'B', "M3", false);
        enigma_m3->set_key("ARE");
        std::cout << "INPUT: ";
        std::cin.getline(input, 100);
        if(!(std::strncmp(input, "quit", 4) == 0))
        {
            std::cout << "OUTPUT: "+enigma_m3->type_phrase(input) << std::endl;
        }
    }

    return 0;
}
