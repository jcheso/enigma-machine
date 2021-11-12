#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <ctype.h>
#include <typeinfo>
#include "helper.h"
#include "errors.h"
#include "inputSwitches.h"
#include "plugboard.h"
#include "rotor.h"
#include "reflector.h"
#include "outputBoard.h"
using namespace std;

int main(int argc, char **argv)
{

    // Initialise vectors to store inputs
    vector<string> plugboardInput;
    vector<string> reflectorInput;
    vector<string> rotorsInput[10];
    vector<string> rotorPosInput;

    // Initialise variable for storing encrypted letter
    int val;
    char ch;
    int numRotors;

    // Construct objects
    vector<Rotor> rotors;
    Plugboard plugboard;
    InputSwitches inputSwitches;
    Reflector reflector;
    OutputBoard outputBoard;

    if (!checkCorrectParameters(argc, argv))
    {
        cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>)* rotor-positions" << endl;
        return INSUFFICIENT_NUMBER_OF_PARAMETERS;
    }

    // Check if Plugboard was supplied, if not default to the standard mapping
    if (!isFileSupplied(argv[1], 'b'))
    {
        plugboard.generateDefaultPlugboard();
        // plugboard.usingDefaultPlugboard = true;
        numRotors = argc - 3;
        // for (size_t i = 0; i < 26; i++)
        // {
        //     plugboardInput.push_back(to_string(i));
        //     plugboardInput.push_back(to_string(i));
        // }
        parseInputStrings(argv[1], reflectorInput);
        for (size_t i = 0; i < numRotors; i++)
            parseInputStrings(argv[2 + i], rotorsInput[i]);
        parseInputStrings(argv[argc - 1], rotorPosInput);
    }
    else
    {
        numRotors = argc - 4;
        parseInputStrings(argv[1], plugboardInput);
        parseInputStrings(argv[2], reflectorInput);
        for (size_t i = 0; i < numRotors; i++)
            parseInputStrings(argv[3 + i], rotorsInput[i]);
        parseInputStrings(argv[argc - 1], rotorPosInput);
    }

    try
    { // Run initialisation methods on objects
        if (isFileSupplied(argv[1], 'b'))
        {
            plugboard.initialisePlugboard(plugboardInput);
        }
        for (size_t i = 0; i < numRotors; i++)
        {
            if (i >= rotorPosInput.size())
            {
                cerr << "No starting position for rotor " << i << " in rotor position file: rotor.pos" << endl;
                return NO_ROTOR_STARTING_POSITION;
            };
            Rotor rotor;
            rotor.initialiseRotor(rotorsInput[i], rotorPosInput[i]);
            rotors.push_back(rotor);
        }
        reflector.initialiseReflector(reflectorInput);

        while (!cin.eof())
        {
            inputSwitches.readInput(val);
            if (cin.fail())
            {
                break;
            }
            plugboard.swapLetter(val, val);
            if (numRotors != 0)
            {
                for (int i = numRotors - 1; i >= 0; i--)
                {
                    int tempVal = val;
                    // Always rotate the right most rotor
                    if (i == numRotors - 1)
                    {
                        rotors[i].rotateRotor();
                        rotors[i].activatedNotch = false;
                    }

                    // Check if the rotor is at a notch (except the leftmost rotorNum=0)
                    // Check if the notch has previously rotated/been activated and not moved since
                    if (i != 0 && rotors[i].checkNotch() && !rotors[i].activatedNotch)
                    {
                        rotors[i].activatedNotch = true;
                        rotors[i - 1].rotateRotor();
                        rotors[i - 1].activatedNotch = false;
                    }
                    rotors[i].mapNumber(val, false);
                }
            }
            reflector.reflectNumber(val, val);

            if (numRotors != 0)
            {
                for (int i = 0; i < numRotors; i++)
                {
                    int tempVal = val;
                    rotors[i].mapNumber(val, true);
                }
            }
            plugboard.swapLetter(val, val);
            outputBoard.mapNum2Letter(val, ch);
        }
    }
    catch (int error)
    {
        return error;
    }
    return NO_ERROR;
}
