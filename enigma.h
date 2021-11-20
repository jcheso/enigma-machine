#ifndef ENIGMA_H
#define ENIGMA_H
#include <string>
#include <vector>
#include "inputSwitches.h"
#include "plugboard.h"
#include "rotor.h"
#include "reflector.h"
using namespace std;

/* The Enigma class houses the objects that make up an Enigma Machine */
class Enigma
{
private:
    // Initialise variables for storing arguments, encrypted letter and numRotors used in the Enigma Machine
    int argCount;
    char **argValues;
    size_t numRotors;
    int letterForEncryption;

    // Initialise vectors to store inputs as strings for further processing
    vector<string> plugboardInput;
    vector<string> reflectorInput;
    vector<string> rotorsInput[10];
    vector<string> rotorPosInput;

    // Instantiate the objects of Enigma machine
    vector<Rotor> rotors;
    Plugboard plugboard;
    InputSwitches inputSwitches;
    Reflector reflector;

public:
    /* This constructor instantiates an Enigma machine object with the main arg count and arg values */
    Enigma(int argc, char **argv);
    /* This method reads in the config files for each of the Enigma machine components */
    int readConfigFiles();
    /* This method instantiates the components of the Enigma machine and performs error checks */
    int initialiseMachine();
    /* This method encrypts a message through the Enigma machine */
    int encryptMessage();
};
#endif