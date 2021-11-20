#include <iostream>
#include <string>
#include <vector>
#include "helper.h"
#include "errors.h"
#include "inputSwitches.h"
#include "plugboard.h"
#include "rotor.h"
#include "reflector.h"
#include "enigma.h"
using namespace std;

Enigma::Enigma(int argc, char **argv) : argCount(argc), argValues(argv) {}

int Enigma::readConfigFiles()
{
    if (!checkCorrectParameters(argCount, argValues))
    {
        cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>)* rotor-positions" << endl;
        throw(INSUFFICIENT_NUMBER_OF_PARAMETERS);
    }

    // This functionality is on the basis that the Enigma machine needs to operate if no plugboard file is provided
    // No plugboard supplied
    if (!isFileSupplied(argValues[1], 'b'))
    {
        numRotors = argCount - 3;
        parseInputToString(argValues[1], reflectorInput);
        for (size_t i = 0; i < numRotors; i++)
            parseInputToString(argValues[2 + i], rotorsInput[i]);
    }
    // Plugboard provided
    else
    {
        numRotors = argCount - 4;
        parseInputToString(argValues[1], plugboardInput);
        parseInputToString(argValues[2], reflectorInput);
        for (size_t i = 0; i < numRotors; i++)
            parseInputToString(argValues[3 + i], rotorsInput[i]);
    }
    parseInputToString(argValues[argCount - 1], rotorPosInput);
    return NO_ERROR;
}

int Enigma::initialiseMachine()
{
    // Initialise the object variables by running functions that error check the provided strings, and returns error codes that are caught and returned to main
    if (isFileSupplied(argValues[1], 'b'))
        plugboard.initialisePlugboard(plugboardInput);
    else
        plugboard.generateDefaultPlugboard();

    // Iterate through the number of rotors and add each rotor object to a vector of rotors.
    for (size_t i = 0; i < numRotors; i++)
    {
        if (i >= rotorPosInput.size())
        {
            cerr << "No starting position for rotor " << i << " in rotor position file: rotor.pos" << endl;
            throw(NO_ROTOR_STARTING_POSITION);
        };
        Rotor rotor;
        rotor.initialiseRotor(rotorsInput[i], rotorPosInput[i]);
        rotors.push_back(rotor);
    }
    reflector.initialiseReflector(reflectorInput);
    return NO_ERROR;
}

int Enigma::encryptMessage()
{
    while (!cin.eof())
    {
        inputSwitches.readInput(letterForEncryption);

        // If the input fails break out and do not encrypt
        if (cin.fail())
            break;

        plugboard.swapLetter(letterForEncryption);

        // Only use rotors if there are rotors supplied
        if (numRotors != 0)
        {
            for (size_t i = numRotors; i > 0; i--)
            {
                // Integer for accessing arrays - if using size_t = numRotors - 1 it will segmentation fault when i goes negative;
                // Therefore need a separate int to avoid any compiler warnings of comparing int to unsigned int.
                int j = i - 1;
                // Always rotate the right most rotor
                if (i == numRotors)
                {
                    rotors[j].rotateRotor();
                    rotors[j].activatedNotch = false;
                }

                // Check if the rotor is at a notch (except the leftmost rotor) and check if it has been activated already
                if (i != 0 && rotors[j].checkNotch() && !rotors[j].activatedNotch)
                {
                    // Set the notch to have been activated
                    rotors[j].activatedNotch = true;
                    rotors[j - 1].rotateRotor();
                    // Set the notch on the rotor to it's left to be deactivated as the rotor has moved since
                    rotors[j - 1].activatedNotch = false;
                }
                rotors[j].mapNumber(letterForEncryption, false);
            }
        }
        reflector.reflectNumber(letterForEncryption);
        if (numRotors != 0)
        {
            for (size_t i = 0; i < numRotors; i++)
                rotors[i].mapNumber(letterForEncryption, true);
        }
        plugboard.swapLetter(letterForEncryption);
        // Conver the num to a char and output
        char ch = letterForEncryption + 'A';
        cout << ch;
    }
    return NO_ERROR;
}
