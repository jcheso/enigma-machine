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
// #include "outputBoard.h"
#include "enigma.h"
using namespace std;

// ** TO DO **
// Parse inputs in each object w/ method that calls helper function
// Enigma method to receive inputs
// Enigma method to initialise objects
// Enigma method to run enigma
// Review against best practices & feedback

/* I have used main to run the Enigma machine over creating an Enigma class to contain all the objects
on the basis that only one is required for this assignment. If multiple were required this code could be
transferred to an Enigma class which has the objects as variables and the methods required to run it as per below.*/
int main(int argc, char **argv)
{

    // Initialise vectors to store inputs as strings for further processing
    // vector<string> plugboardInput;
    // vector<string> reflectorInput;
    // vector<string> rotorsInput[10];
    // vector<string> rotorPosInput;

    // Initialise variable for storing encrypted letter and numRotors used in the Enigma Machine
    // int letterForEncryption;
    // int numRotors;

    // if (!checkCorrectParameters(argc, argv))
    // {
    //     cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>)* rotor-positions" << endl;
    //     return INSUFFICIENT_NUMBER_OF_PARAMETERS;
    // }

    /* Construct the objects of Enigma machine without the input vectors, as we need to return error codes if any are erranous*/
    // vector<Rotor> rotors;
    // Plugboard plugboard;
    // InputSwitches inputSwitches;
    // Reflector reflector;
    // OutputBoard outputBoard;

    Enigma enigma(argc, argv);
    try
    {
        enigma.readInputFiles();
        enigma.initialise();
        enigma.encrypt();

        // Check if Plugboard was supplied, if not default to the standard mapping and try reading in the files, if an error is encountered return it to main
        // if (!isFileSupplied(argv[1], 'b'))
        // {
        //     numRotors = argc - 3;
        //     parseInputToString(argv[1], reflectorInput);
        //     for (int i = 0; i < numRotors; i++)
        //         parseInputToString(argv[2 + i], rotorsInput[i]);
        // }
        // else
        // {
        //     numRotors = argc - 4;
        //     parseInputToString(argv[1], plugboardInput);
        //     parseInputToString(argv[2], reflectorInput);
        //     for (int i = 0; i < numRotors; i++)
        //         parseInputToString(argv[3 + i], rotorsInput[i]);
        // }
        // parseInputToString(argv[argc - 1], rotorPosInput);

        // Initialise the objects by running functions that error check the provided strings, and returns error codes that are caught and returned to main
        // if (isFileSupplied(argv[1], 'b'))
        //     plugboard.initialisePlugboard(plugboardInput);
        // else
        //     plugboard.generateDefaultPlugboard();

        // for (int i = 0; i < numRotors; i++)
        // {
        //     if (i >= rotorPosInput.size())
        //     {
        //         cerr << "No starting position for rotor " << i << " in rotor position file: rotor.pos" << endl;
        //         return NO_ROTOR_STARTING_POSITION;
        //     };
        //     Rotor rotor;
        //     rotor.initialiseRotor(rotorsInput[i], rotorPosInput[i]);
        //     rotors.push_back(rotor);
        // }
        // reflector.initialiseReflector(reflectorInput);

        // Run the Enigma Machine while there is input
        // while (!cin.eof())
        // {
        //     inputSwitches.readInput(letterForEncryption);
        //     if (cin.fail())
        //     {
        //         break;
        //     }
        //     plugboard.swapLetter(letterForEncryption);
        //     if (numRotors != 0)
        //     {
        //         for (int i = numRotors - 1; i >= 0; i--)
        //         {
        //             // Always rotate the right most rotor
        //             if (i == numRotors - 1)
        //             {
        //                 rotors[i].rotateRotor();
        //                 rotors[i].activatedNotch = false;
        //             }
        //             // Check if the rotor is at a notch (except the leftmost rotor) and check if it has been activated already
        //             if (i != 0 && rotors[i].checkNotch() && !rotors[i].activatedNotch)
        //             {
        //                 // Set the notch to have been activated
        //                 rotors[i].activatedNotch = true;
        //                 rotors[i - 1].rotateRotor();
        //                 // Set the notch on the rotor to it's left to be unactivated as the rotor has moved since
        //                 rotors[i - 1].activatedNotch = false;
        //             }
        //             rotors[i].mapNumber(letterForEncryption, false);
        //         }
        //     }
        //     reflector.reflectNumber(letterForEncryption);
        //     if (numRotors != 0)
        //     {
        //         for (int i = 0; i < numRotors; i++)
        //             rotors[i].mapNumber(letterForEncryption, true);
        //     }
        //     plugboard.swapLetter(letterForEncryption);
        //     outputBoard.outputLetter(letterForEncryption);
        // }
    }
    catch (int error)
    {
        return error;
    }
    return NO_ERROR;
}
