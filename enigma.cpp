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
#include "enigma.h"
using namespace std;

Enigma::Enigma(int argc, char **argv) : argCount(argc), argValues(argv) {}

int Enigma::readInputFiles()
{
    if (!checkCorrectParameters(argCount, argValues))
    {
        cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>)* rotor-positions" << endl;
        throw(INSUFFICIENT_NUMBER_OF_PARAMETERS);
    }

    // Check if Plugboard was supplied, if not default to the standard mapping and try reading in the files, if an error is encountered return it to main
    if (!isFileSupplied(argValues[1], 'b'))
    {
        numRotors = argCount - 3;
        parseInputToString(argValues[1], reflectorInput);
        // Go through each rotor and copy it to a vector containing rotor arrays
        for (int i = 0; i < numRotors; i++)
            parseInputToString(argValues[2 + i], rotorsInput[i]);
    }
    else
    {
        numRotors = argCount - 4;
        parseInputToString(argValues[1], plugboardInput);
        parseInputToString(argValues[2], reflectorInput);
        // Go through each rotor and copy it to a vector containing rotor arrays
        for (int i = 0; i < numRotors; i++)
            parseInputToString(argValues[3 + i], rotorsInput[i]);
    }
    parseInputToString(argValues[argCount - 1], rotorPosInput);
}

int Enigma::initialise()
{
    // Initialise the objects by running functions that error check the provided strings, and returns error codes that are caught and returned to main
    if (isFileSupplied(argValues[1], 'b'))
        plugboard.initialisePlugboard(plugboardInput);
    else
        plugboard.generateDefaultPlugboard();

    for (int i = 0; i < numRotors; i++)
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
}

int Enigma::encrypt()
{
    while (!cin.eof())
    {
        inputSwitches.readInput(letterForEncryption);
        if (cin.fail())
            break;
        plugboard.swapLetter(letterForEncryption);
        if (numRotors != 0)
        {
            for (int i = numRotors - 1; i >= 0; i--)
            {
                // Always rotate the right most rotor
                if (i == numRotors - 1)
                {
                    rotors[i].rotateRotor();
                    rotors[i].activatedNotch = false;
                }
                // Check if the rotor is at a notch (except the leftmost rotor) and check if it has been activated already
                if (i != 0 && rotors[i].checkNotch() && !rotors[i].activatedNotch)
                {
                    // Set the notch to have been activated
                    rotors[i].activatedNotch = true;
                    rotors[i - 1].rotateRotor();
                    // Set the notch on the rotor to it's left to be unactivated as the rotor has moved since
                    rotors[i - 1].activatedNotch = false;
                }
                rotors[i].mapNumber(letterForEncryption, false);
            }
        }
        reflector.reflectNumber(letterForEncryption);
        if (numRotors != 0)
        {
            for (int i = 0; i < numRotors; i++)
                rotors[i].mapNumber(letterForEncryption, true);
        }
        plugboard.swapLetter(letterForEncryption);
        // outputBoard.outputLetter(letterForEncryption);

        char ch = letterForEncryption + 'A';
        cout << ch;
    }
}
