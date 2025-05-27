#include "Enigma.hxx"

#include <iostream>
#include <algorithm>
#include <cctype>

void apply_rsg(const std::vector<int> ringstellung, Enigma& eg)
{
    for(unsigned int i{0}; i < ringstellung.size(); ++i)
    {
        eg.ringstellung(eg.getRotorLabels()[i], ringstellung[i]);
    }
}

bool is_word(const std::string& s)
{
    for(auto i : s)
    {
        if(!std::isalpha(i)) return false;
    }

    return true;
}

int main(int argc, char** argv)
{
    
    std::string eg_version = EnigmaInfo::version;

    if(EnigmaInfo::isBeta)
    {
        eg_version += " (BETA)";
    }

    std::string intro = "===========================================\n\n"
    "  WELCOME TO THE ENIGMA ENCODER\n"+
    std::string(18-eg_version.size()/2, ' ')+eg_version;
    intro += "\n        Kristian Zarebski\n\n"
    "===========================================\n"
    "Type 'quit' to exit.\n\n";

    std::cout << intro;

    std::string choice = "";
    std::vector<int> rotors = {2,3,4};
    std::string key = "YES";

    int safety_count = 0;

    while(choice != "Y" && choice != "N")
    {
        std::cout << "Set key? [y/n] ";
        std::cin >> choice;
        std::cout << std::endl;

        std::transform(choice.begin(), choice.end(), choice.begin(), [](const char c){ return std::toupper(c);});

        safety_count++;
        if(safety_count > 10)
        {
            std::cout << "Program Timeout." << std::endl;
            return -1;
        }
    }

    safety_count = 0;

    if(choice == "Y")
    {
        std::cout << "Enter 3/4 character key for M3 or M4 machine: ";
        std::cin >> key;
        std::cout << std::endl;

        while( ( key.size() != 3 && key.size() != 4 ) || !is_word(key))
        {
            std::cout << "Key must be of size 3 or 4 and alpha values only: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> key;
            std::cout << std::endl;
        }        
    }

    choice = "";

    while(choice != "Y" && choice != "N")
    {
        std::cout << "Set Rotors? [y/n] ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> choice;
        std::cout << std::endl;
        
        std::transform(choice.begin(), choice.end(), choice.begin(), [](const char c){ return std::toupper(c);});

        safety_count++;
        if(safety_count > 10)
        {
            std::cout << "Program Timeout." << std::endl;
            return -1;
        }
    }
    
    safety_count = 0;

    if(choice == "Y")
    {
        rotors = {};
        int _temp = -1;
        std::cout << "Enter "+std::to_string(key.size())+" rotor types individually: \n";
        for(unsigned int i{0}; i < key.size(); ++i)
        {
            std::cout << "Rotor "+std::to_string(i+1)+": ";
            std::cin >> _temp;            

            while(_temp < 1 || _temp > 8 || std::find(rotors.begin(), rotors.end(), _temp) != std::end(rotors))
            {
                std::cout << "Invalid Rotor Choice! Rotor type must be 1-8 and be unique: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin >> _temp;
            }
            rotors.push_back(_temp);
        }
    }

    auto enigma = std::make_unique<Enigma>(rotors, 'B', (key.size() == 3) ? EnigmaType::M3 : EnigmaType::M4, false);

    enigma->set_key(key);

    std::vector<int> rsg_settings = {0,0,0,0};

    choice = "";

    while(choice != "Y" && choice != "N")
    {
        std::cout << "Ringstellung? [y/n] ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> choice;
        std::cout << std::endl;
        
        std::transform(choice.begin(), choice.end(), choice.begin(), [](const char c){ return std::toupper(c);});

        safety_count++;
        if(safety_count > 10)
        {
            std::cout << "Program Timeout." << std::endl;
            return -1;
        }
    }

    safety_count = 0;

    if(choice == "Y")
    {
        rsg_settings = {};
        int _temp = -1;
        std::cout << "Set Number of Internal Wiring Rotation Increments for Each of the "+std::to_string(key.size())+" Rotors:\n";
        for(unsigned int i{0}; i < key.size(); ++i)
        {
            std::cout << "Rotor "+std::to_string(i+1)+": ";
            std::cin >> _temp;
            while(_temp < 0 && !std::isdigit(_temp))
            {
                std::cout << "Rotation increments must be a positive integer: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin >> _temp;
                safety_count++;
                if(safety_count > 10)
                {
                    std::cout << "Program Timeout." << std::endl;
                    return -1;
                }
            }
            safety_count = 0;
            std::cout << std::endl;
            rsg_settings.push_back(_temp);
        }

        apply_rsg(rsg_settings, *enigma);
    }

    char input[100] = {0};
    std::cin.ignore(1);
    while(!(std::strncmp(input, "quit", 4) == 0))
    {
        std::cout << "INPUT: ";
        std::cin.getline(input, 100);
        if(!(std::strncmp(input, "quit", 4) == 0))
        {
            if(std::strncmp(input, "reset", 4) == 0)
            {
                std::cout << "Resetting Machine..." << std::endl;
                enigma->reset();
                enigma->set_key(key);
                apply_rsg(rsg_settings, *enigma);
            }
            else
            {
                std::cout << "OUTPUT: "+enigma->type_phrase(input) << std::endl;
            }
        }
    }
    return 0;
}
