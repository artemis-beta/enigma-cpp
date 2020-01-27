# ENIGMA
This is a small application written in C++ which simulates both the M3 and M4, 3 and 4 rotor variants of the Enigma machine which was utilised by German forces during WWII to encode information. It is a copy of the Python version found [here](https://github.com/artemis-beta/enigma).

## Prerequisites

Enigma uses the [Boost C++ library](https://www.boost.org/users/history/version_1_72_0.html) which should be installed first. It also makes use of a custom logging class that I have written and is automatically fetched and installed.

## App

Currently the repository is in beta. You can use the included Enigma app by building it using the `install` script.

The script takes one optional argument which sets the required `$BOOSTINCLUDE` environment variable. This should point to the location of `boost/include/boost`

```
$ ./install --boost-libs <boost-include>
```

the script should retrieve also the required [Logging](https://github.com/artemis-beta/cpp-logger) library for the logger. The resultant executable can then be found as `enigma_app` within the newly created `bin` directory.

Running the app will allow the user to specify settings such as the key, the rotor type choice (unique numbers from 1-8), and rotating the internal wiring within each rotor (Ringstellung). The user enters then enters their input next to the `INPUT: ` prompt. The machine can be reset at any point to the start settings for decoding using the `reset` command within the app. Quit the application using the `quit` command.

## Custom Machine

To create a new instance of Enigma the default can be used which is an M3 instance with pre-selected rotor arrangement and reflector choice, or all settings can be chosen by the user. Note as with the machine itself, one of the 8 numbered rotor types may only be selected once.

```
#include "Enigma.hxx"

#include <vector>
#include <string>
#include <iostream>

int main(int argc, char** argv)
{
    const std::vector<int> my_rotor_list = {1, 4, 6, 4}; // 3 or 4 of 1,2,3,4,5,6,7,8
    const char my_reflector = 'B';                       // 'B' or 'C'
    const std::string machine_type = "M4";               // 'M3' or 'M4' (should match rotor list)
    const bool debug_mode = false;                       // Run Enigma in debug mode

    Enigma* enigma = new Enigma( my_rotor_list, my_reflector, machine_type, debug_mode );

    enigma->ringstellung("right", 2);   // Perform an internal wire rotation on the right rotor of 2 steps
                                        // for M3 the rotors are {"left", "middle", "right"}
                                        // for M4 the rotors are {"left", "middle left", "middle right", "right"}
    
    const std::string key = "NERO";
    const std::string phrase = "NOBODYEXPECTSTHESPANISHINQUISITION";

    enigma->set_key(key);
    
    const std::string cipher = enigma->type_phrase(phrase);

    std::cout << phrase << " -> " << cipher;

    return 0;
}
```