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
using namespace std;

/* This class models a Rotor */
class Rotor
{
    vector<int> rotorMap;
    vector<int> originalRotorMap;
    vector<int> notches;
    bool hasNotch = false;
    int startPosition;
    int mappedNumber;

    /* This method gets the start position of the rotor from the config provided */
    int getStartPosition(string config)
    {
        string tempStartPosition;
        // If does not exist, exit with NO_ROTOR_STARTING_POSITION
        try
        {
            tempStartPosition = config;
        }
        catch (...)
        {
            throw(NO_ROTOR_STARTING_POSITION);
        }
        // Check isNumeric()
        if (!isNumeric(tempStartPosition))
        {
            cerr << "Non-numeric character in rotor positions file rotor.pos" << endl;
            throw(NON_NUMERIC_CHARACTER);
        }
        startPosition = stoi(tempStartPosition);
        // Check isValidNum() and return error code if false
        if (!isValidNum(startPosition))
        {
            cerr << "Invalid index provided" << endl;
            throw(INVALID_INDEX);
        }
        return NO_ERROR;
    }

    /* This method sets the start position of the rotor */
    void setStartPosition()
    {
        for (int i = 0; i < startPosition; i++)
            rotateRotor();
    }

public:
    int rotorNum;
    int rotations = 0;
    bool activatedNotch = false;
    /* This method initialises a rotor from a provided config file */
    int initialiseRotor(vector<string> config, int rotorNum, string rotorPosInput)
    {
        this->rotorNum = rotorNum;
        // Check isValidLen()
        if (config.size() < 26)
        {
            cerr << "Not all inputs mapped in rotor file: rotor.rot" << endl;
            throw(INVALID_ROTOR_MAPPING);
        }
        for (size_t i = 0; i < config.size(); i++)
        {
            int num;
            int index;
            // Check isNumeric() & convert to int if true. Return error code if false
            if (isNumeric(config[i]))
                num = stoi(config[i]);
            else
            {
                cerr << "Non-numeric character for mapping in rotor file rotor.rot" << endl;
                throw(NON_NUMERIC_CHARACTER);
            }
            // Check isValidNum() and return error code if false
            if (!isValidNum(num))
            {
                cerr << "Invalid index provided" << endl;
                throw(INVALID_INDEX);
            }
            if (isInArray(num, rotorMap, index) && i < 26)
            {
                cerr << "Invalid mapping of input " << i << " to output " << num << " (output " << num << " is already mapped to from input " << index << ") in rotor file: rotor.rot" << endl;
                throw(INVALID_ROTOR_MAPPING);
            }
            // Add to rotorMap if its in the first 25 digits
            if (i < 26)
                rotorMap.push_back(num);
            // Add to notches if its past the first 25 digits and set this rotor to have notches
            if (i >= 26)
            {
                notches.push_back(num);
                hasNotch = true;
            }
        }
        originalRotorMap = rotorMap;
        getStartPosition(rotorPosInput);
        setStartPosition();
        return NO_ERROR;
    }
    /* This method rotates the rotor specified*/
    void rotateRotor()
    {
        // Shift rotorMap array to the right by one
        int first = rotorMap[0] - 1;
        if (first < 0)
            first = 25;
        for (int i = 0; i < rotorMap.size(); i++)
        {
            rotorMap[i] = (rotorMap[i + 1] - 1);
            if (rotorMap[i] < 0)
                rotorMap[i] = 25;
        }
        rotorMap[rotorMap.size() - 1] = first;
        rotations++;
    }
    /* This method maps the input number to the output number */
    void mapNumber(int &num, bool reflected)
    {
        if (!reflected)
            num = rotorMap[num];
        else
            isInArray(num, rotorMap, num);
    }
    /* This method checks if the notch is at 12 o'clock */
    bool checkNotch()
    {
        // Iterate through notches & check if the current rotation is at the notch
        for (int i = 0; i < notches.size(); i++)
        {
            if (rotations == notches[i])
                return true;
        }
        return false;
    }
};

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

    // do
    // {
    //     n = runEnigma(inputSwitches, plugboard, rotorPosInput, rotors, val, ch, reflector, outputBoard);
    // } while (n == 0);

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
            rotor.initialiseRotor(rotorsInput[i], i, rotorPosInput[i]);
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
            // cout << "Number in: " << val;
            plugboard.swapLetter(val, val);
            // cout << "Plugboard swapped to: " << val << endl;
            if (numRotors != 0)
            {
                for (int i = numRotors - 1; i >= 0; i--)
                {
                    int tempVal = val;

                    // Always rotate the right most rotor
                    if (rotors[i].rotorNum == numRotors - 1)
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
                    // val = val + rotors[i].rotations;
                    rotors[i].mapNumber(val, false);
                    // cout << " Rotor " << i << ": " << val;
                    // cout << "With rotations" << val << endl;
                }
            }
            reflector.reflectNumber(val, val);
            // cout << " Reflector: " << val;
            if (numRotors != 0)
            {
                for (int i = 0; i < numRotors; i++)
                {
                    int tempVal = val;
                    rotors[i].mapNumber(val, true);
                    // cout << " Rotor: " << i << ": " << val;
                    // val += ((rotors[i].rotations) + 26) % 26;
                    // cout << "With rotations" << val << endl;
                }
            }
            plugboard.swapLetter(val, val);
            // cout << " Number out: " << val << endl;
            outputBoard.mapNum2Letter(val, ch);
        }
    }
    catch (int error)
    {
        return error;
    }
    return NO_ERROR;
}