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
using namespace std;

class Reflector
{
    // Define any private variables and methods here
    vector<int> array1;
    vector<int> array2;
    int reflectedNumber;
    int index;
    // Define any public variables and methods here
public:
    /* This method initialises a reflector from a provided config file */
    int initialiseReflector(vector<string> config)
    {
        int num;
        // Check isValidLen()
        if ((config.size() % 2 == 0) && config.size() != 26)
        {
            cerr << "Insufficient number of mappings in reflector file: reflector.rf" << endl;
            throw(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
        }
        else if ((config.size() % 2 != 0) && config.size() != 26)
        {
            cerr << "Incorrect (odd) number of parameters in reflector file reflector.rf" << endl;
            throw(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
        }

        for (int i = 0; i < config.size(); i++)
        {
            // Check isNumeric() & convert to int if true. Return error code if false
            if (isNumeric(config[i]))
                num = stoi(config[i]);
            else
            {
                cerr << "Non-numeric character in reflector file reflector.rf" << endl;
                throw(NON_NUMERIC_CHARACTER);
            }
            // Check isValidNum() and return error code if false
            if (!isValidNum(num))
            {
                cerr << "Invalid index provided" << endl;
                throw(INVALID_INDEX);
            }
            // Check if is an input or output value, then check if it isInArray(). If not, push to array, else return error
            if (!isInArray(num, array2) && !isInArray(num, array1))
            {
                if (i % 2 == 0)
                    array1.push_back(num);
                else
                    array2.push_back(num);
            }
            else
            {
                cerr << "Incorrect (odd) number of parameters in reflector file reflector.rf" << endl;
                throw(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
            }
        }
        return NO_ERROR;
    }
    void reflectNumber(int input, int &output)
    {
        int arrayPosition;
        if (isInArray(input, array1, arrayPosition))
            output = array2[arrayPosition];
        else if (isInArray(input, array2, arrayPosition))
            output = array1[arrayPosition];
    }
};

class OutputBoard
{
    // Define any private variables and methods here
    char outputLetter;
    // Define any public variables and methods here
public:
    /* This method takes a number and returns the corresponding character */
    void mapNum2Letter(int num, char ch)
    {
        ch = static_cast<char>(num + 65);
        cout << ch;
    }
};

int main(int argc, char **argv)
{
    // argv[0] = "c:/Users/jches/Documents/Programming/MSc Computing/Intro to C++/Coursework #2/main.exe";
    // // argv[1] = "plugboards/IV.pb";
    // argv[1] = "reflectors/test.rf";
    // // argv[3] = "rotors/I.rot";
    // argv[2] = "rotors/test1.rot";
    // argv[3] = "rotors/test2.rot";
    // argv[4] = "rotors/test.pos";
    // argc = 5;

    if (argc < 3)
    {
        cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>)* rotor-positions" << endl;
        return INSUFFICIENT_NUMBER_OF_PARAMETERS;
    }

    // Initialise vectors to store inputs
    vector<string> plugboardInput;
    vector<string> reflectorInput;
    vector<string> rotorsInput[100];
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

    // Check if Plugboard was supplied, if not default to the standard mapping
    string plugboardTest = argv[1];
    if (!plugboardSupplied(plugboardTest))
    {
        plugboard.usingDefaultPlugboard = true;
        numRotors = argc - 3;
        for (int i = 0; i < 26; i++)
        {
            plugboardInput.push_back(to_string(i));
            plugboardInput.push_back(to_string(i));
        }

        parseInputStrings(argv[1], reflectorInput);

        for (int i = 0; i < numRotors; i++)
            parseInputStrings(argv[2 + i], rotorsInput[i]);

        parseInputStrings(argv[argc - 1], rotorPosInput);
    }
    else
    {
        numRotors = argc - 4;
        parseInputStrings(argv[1], plugboardInput);
        parseInputStrings(argv[2], reflectorInput);

        for (int i = 0; i < numRotors; i++)
            parseInputStrings(argv[3 + i], rotorsInput[i]);

        parseInputStrings(argv[argc - 1], rotorPosInput);
    }

    // Check if rotor start positions are supplied, throw an error if not
    string rotorPosTest = argv[argc - 1];
    if (!rotorSupplied(rotorPosTest))
    {
        cerr << "Invalid rotor configuration" << endl;
        throw(INSUFFICIENT_NUMBER_OF_PARAMETERS);
    }

    try
    { // Run initialisation methods on objects
        plugboard.initialisePlugboard(plugboardInput);
        for (int i = 0; i < numRotors; i++)
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
                    if (i != 0)
                    {
                        if (rotors[i].checkNotch() && !rotors[i].activatedNotch)
                        {
                            rotors[i].activatedNotch = true;
                            rotors[i - 1].rotateRotor();
                            rotors[i - 1].activatedNotch = false;
                        }
                    }
                    rotors[i].mapNumber(val, false);
                    // cout << " - R" << rotors[i].rotorNum << " : " << val;
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
            // cout << " - PB: " << val << endl;

            outputBoard.mapNum2Letter(val, ch);
        }
    }
    catch (int error)
    {
        return error;
    }
    return NO_ERROR;
}