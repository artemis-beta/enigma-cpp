# ENIGMA
This is a small application written in C++ which simulates both the M3 and M4, 3 and 4 rotor variants of the Enigma machine which was utilised by German forces during WWII to encode information. It is a copy of the Python version found [here](https://github.com/artemis-beta/enigma).

## Prerequisites

Enigma uses the [Boost C++ library](https://www.boost.org/users/history/version_1_72_0.html) which should be installed first. It also makes use of a custom logging class that I have written and is automatically fetched and installed.

## Beta Testing

Currently the repository is in beta. You can use the included Enigma app by building it using the `install` script.

The script takes one optional argument which sets the required `$BOOSTINCLUDE` environment variable. This should point to the location of `boost/include/boost`

```
$ ./install --boost-libs <boost-include>
```

the script should retrieve also the required [Logging](https://github.com/artemis-beta/cpp-logger) library for the logger. The resultant executable can then be found as `enigma_app` within the newly created `bin` directory.

Running the app will allow the user to specify settings such as the key, the rotor type choice (unique numbers from 1-8), and rotating the internal wiring within each rotor (Ringstellung). The user enters then enters their input next to the `INPUT: ` prompt. The machine can be reset at any point to the start settings for decoding using the `reset` command within the app. Quit the application using the `quit` command.
