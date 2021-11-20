#ifndef ENIGMA_H
#define ENIGMA_H
#include <iostream>
#include <string>
#include <vector>
#include "helper.h"
#include "errors.h"
#include "inputSwitches.h"
#include "plugboard.h"
#include "rotor.h"
#include "reflector.h"
#include "outputBoard.h"
using namespace std;

class Enigma
{
private:
    // Initialise vectors to store inputs as strings for further processing
    vector<string> plugboardInput;
    vector<string> reflectorInput;
    vector<string> rotorsInput[10];
    vector<string> rotorPosInput;

    // Initialise variable for storing encrypted letter and numRotors used in the Enigma Machine
    int numRotors;
    int letterForEncryption;
    int argCount;
    char **argValues;

    /* Construct the objects of Enigma machine without the input vectors, as we need to return error codes if any are erranous*/
    vector<Rotor> rotors;
    Plugboard plugboard;
    InputSwitches inputSwitches;
    Reflector reflector;
    OutputBoard outputBoard;

public:
    Enigma(int argc, char **argv);
    int readInputFiles();
    int initialise();
    int encrypt();
};
#endif