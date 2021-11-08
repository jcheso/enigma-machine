#include <iostream>
#include <fstream>
#include "errors.h"
#include <string>
#include <vector>
#include <array>
#include <ctype.h>
#include <typeinfo>

using namespace std;

/* This function takes an input string and assigns the contents to an array - Save as vector of strings instead of int?*/
int parseInputStrings(char array[], vector<string> &arrayOut);
/* This function checks if a plugboard was provided */
bool plugboardSupplied(string plugboardTest);
/* This function checks if a rotor starting position was provided */
bool rotorSupplied(string rotorPosTest);
/* This function takes a string array and prints it */
void printArray(vector<string> &array);
/* This function takes an integer array and prints it */
void printArray(vector<int> &array);
/* This function calculates the modulus and returns the new integer */
int takeModulus(int n);
/* ---- ERROR CHECKS - RETURN THE CORRECT ERROR CODE WITHIN THE CLASS */
/* This function checks if the input is numeric */
bool isNumeric(string ch);
/* This function checks if the input is in the range of 0-25 */
bool isValidNum(int num);
/* This function checks if the array is the expected length */
bool isValidLen(int n, vector<int> array);
/* This function checks if the value is already in the array */
bool isInArray(int n, vector<int> array);
/* This function checks if the value is already in the array and returns the position */
bool isInArray(int n, vector<int> array, int &arrayPosition);
/* This class models the Input Switches */
class InputSwitches
{
    // This vector keeps track of all the input characters
    string input;
    char ch;
    int num;

    // Define any public variables and methods here
public:
    /* This method reads in a character and returns an integer corresponding to it's position in the Alphabet */
    int readInput(int &num)
    {
        cout << "Enter a capital letter to encrypt: ";
        cin >> ch;
        num = ch - 65;
        // cin.ignore(256, '\n');
        if (!isValidNum(num))
        {
            cerr << "Invalid input character, must be a character from A-Z!" << endl;
            return INVALID_INPUT_CHARACTER;
        }
        return NO_ERROR;
    }
};

/* This class models the Plugboard */
class Plugboard
{
    // Define any private variables and methods here
    vector<int> array1;
    vector<int> array2;

    /* This method fills the remainder of the plugboard with the missing characters */
    void fillArray(vector<int> &array1, vector<int> &array2)
    {
        // Iterate from 0 to 25 and check if the value is in the input array
        for (int i = array1.size(); i < 13; i++)
        {
            int sum2add;
            for (int j = 0; j < 26; j++)
            {
                // If not in index, append value to input and output arrays.
                if (!isInArray(j, array1) && !isInArray(j, array2))
                {
                    sum2add = j;
                    break;
                }
            }
            array1.push_back(sum2add);
            array2.push_back(sum2add);
        }
    };
    // Define any public variables and methods here
public:
    /* This method takes in a config file and initialises the plugboard array, if no array is
    provided it will initialise a default 1 to 1 plugboard */
    int initialisePlugboard(vector<string> config)
    {
        if (plugboardSupplied)
        {
            int num;
            // If no plugboard was provided, then convert strings to ints, else perform the checks
            // **Start Loop**
            for (int i = 0; i < config.size(); i++)
            {
                // Check isNumeric() & convert to int if true. Return error code if false
                if (isNumeric(config[i]))
                {
                    num = stoi(config[i]);
                }
                else
                {
                    cerr << "Non numeric character provided";
                    return NON_NUMERIC_CHARACTER;
                }

                // Check isValidNum() and return error code if false
                if (!isValidNum(num))
                {
                    cerr << "Invalid index provided" << endl;
                    return INVALID_INDEX;
                }

                // Check if is an input or output value, then check if it isInArray(). If not, push to array, else return error
                if (i % 2 == 0)
                {
                    if (!isInArray(num, array1))
                    {
                        array1.push_back(num);
                    }
                    else
                    {
                        cerr << "This number is already in the input array" << endl;
                        return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
                    }
                }
                else
                {
                    if (!isInArray(num, array2))
                    {
                        array2.push_back(num);
                    }
                    else
                    {
                        cerr << "This number is already in the output array" << endl;
                        return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
                    }
                }
            }

            // Check if length of input array is less than 26, if so run fillArray on both arrays
            if (config.size() < 26)
            {
                fillArray(array1, array2);
            }
            // Check isValidLen()
            if (!isValidLen(13, array1))
            {
                cerr << "Incorrect number of plugboard parameters" << endl;
                return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
            }
        }
        // Return 0 if no error
        return 0;
    }

    /* This class method takes in an input and swaps it to the correct output */
    int swapLetter(int input, int &output)
    {
        int arrayPosition;
        if (isInArray(input, array1, arrayPosition))
        {
            output = array2[arrayPosition];
            cout << "Plugboard swapped " << input << " to " << output << endl;
            // return output;
        }
        else if (isInArray(input, array2, arrayPosition))
        {
            output = array1[arrayPosition];
            cout << "Plugboard swapped " << input << " to " << output << endl;
            // return output;
        }
    }
};

/* This class models a Rotor */
class Rotor
{
    // Define any private variables and methods here
    vector<int> rotorMap;
    vector<int> originalRotorMap;
    vector<int> notches;
    bool hasNotch = false;
    int rotations = 0;
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
            return NO_ROTOR_STARTING_POSITION;
        }
        // Check isNumeric()
        if (!isNumeric(tempStartPosition))
        {
            cerr << "Non numeric character provided";
            return NON_NUMERIC_CHARACTER;
        }
        // Check isValidNum() and return error code if false
        if (!isValidNum(startPosition))
        {
            cerr << "Invalid index provided" << endl;
            return INVALID_INDEX;
        }
        // Set startPosition to value
        startPosition = stoi(tempStartPosition);
    }

    /* This method sets the start position of the rotor */
    int setStartPosition()
    {
        // Calculate the required rotations as Modulus of (26-rotorMap[startPosition] + startPosition)
        // int initialRotations;
        // initialRotations = (26 - rotorMap[startPosition] + startPosition) % 2;
        cout << "Initial Rotations required to align A with start index of: " << rotorMap[startPosition] << " = " << startPosition << " rotations" << endl;

        for (int i = 0; i < startPosition; i++)
        {
            rotateRotor();
        }
        cout << "Rotated array is: ";
        printArray(rotorMap);
        rotations += startPosition;
    }
    // Define any public variables and methods here
public:
    int rotorNum;

    /* This method initialises a rotor from a provided config file */
    int initialiseRotor(vector<string> config, int rotorNum, string rotorPosInput)
    {
        this->rotorNum = rotorNum;
        // Initialise an iterator
        for (int i = 0; i < config.size(); i++)
        {
            int num;
            // Check isNumeric() & convert to int if true. Return error code if false
            if (isNumeric(config[i]))
            {
                num = stoi(config[i]);
            }
            else
            {
                cerr << "Non numeric character provided";
                return NON_NUMERIC_CHARACTER;
            }

            // Check isValidNum() and return error code if false
            if (!isValidNum(num))
            {
                cerr << "Invalid index provided" << endl;
                return INVALID_INDEX;
            }

            // Check isInArray(rotorMap)
            if (isInArray(num, rotorMap) && i < 26)
            {
                cerr << "Invalid Rotor Mapping" << endl;
                return INVALID_ROTOR_MAPPING;
            }
            // Add to rotorMap if its in the first 25 digits
            if (i < 26)
            {
                rotorMap.push_back(num);
            }
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
        return 0;
    }

    /* This method rotates the rotor specified*/
    void rotateRotor()
    {
        // Shift rotorMap array to the right by one
        int last = rotorMap[rotorMap.size() - 1];
        for (int i = rotorMap.size() - 1; i > 0; i--)
        {
            rotorMap[i] = rotorMap[i - 1];
        }

        rotorMap[0] = last;
    }
    /* This method maps the input number to the output number */
    int mapNumber(int &num)
    {
        num = rotorMap[num];
        // If it has a notch
        // checkNotch()
        // If it is rotor 1, rotate rotor (does this happen if rotates from a notch as well?)
        // return the rotorMap[num] as the mappedNumber
    }
    /* This method checks if the notch is at 12 o'clock */
    bool checkNotch()
    {
        // Iterate through notches
        for (size_t i = 0; i < notches.size(); i++)
            // Check if the current rotation is at the notch
            if (rotorMap[0] == originalRotorMap[notches[i]])
                return true;

        return false;
    }
};

class Reflector
{
    // Define any private variables and methods here
    vector<int> arr1;
    vector<int> arr2;
    int reflectedNumber;
    int index;
    // Define any public variables and methods here
public:
    /* This method initialises a reflector from a provided config file */
    int initialiseReflector(vector<string> config)
    {
        // **Start Loop**
        // Check isNumeric()
        // Check isValidNum()
        // Check isInArray(arr1)
        // Check isInArray(arr2)
        // If value is odd - assign to input array
        // If value is even - assign to output array
        // **End Loop**
        // Check if length of arrays are less than 13,
        // Check isValidLen(arr1)
        // Check isValidLen(arr2)
        // Return 0 if no error
    }
    int reflectNumber(int num)
    {
        // Iterate through array 1 to find input
        // If in array 1, save the index
        // Return reflectedNumber = array2[index]
        // If not in array 1, check the same for array2
    }
};

class OutputBoard
{
    // Define any private variables and methods here
    char outputLetter;
    // Define any public variables and methods here
public:
    /* This method takes a number and returns the corresponding character */
    char mapNum2Letter(int num)
    {
        // Use ASCII to return the num as outputLetter
    }
};

int main(int argc, char **argv)
{
    // Correct input
    // argv[0] = "c:/Users/jches/Documents/Programming/MSc Computing/Intro to C++/Coursework #2/main.exe";
    // argv[1] = "plugboards/IV.pb";
    // argv[2] = "reflectors/I.rf";
    // argv[3] = "rotors/II.rot";
    // argv[4] = "rotors/I.pos";
    // argc = 5;

    // Correct input, multiple rotors
    argv[0] = "c:/Users/jches/Documents/Programming/MSc Computing/Intro to C++/Coursework #2/main.exe";
    argv[1] = "plugboards/IV.pb";
    argv[2] = "reflectors/I.rf";
    argv[3] = "rotors/I.rot";
    argv[4] = "rotors/II.rot";
    argv[5] = "rotors/III.rot";
    argv[6] = "rotors/II.pos";
    argc = 7;

    // No plugboard, use default
    // argv[0] = "c:/Users/jches/Documents/Programming/MSc Computing/Intro to C++/Coursework #2/main.exe";
    // argv[1] = "reflectors/I.rf";
    // argv[2] = "rotors/I.rot";
    // argv[3] = "rotors/II.rot";
    // argv[4] = "rotors/III.rot";
    // argv[5] = "rotors/I.pos";
    // argc = 6;

    // No plugboard or rotor, invalid
    // argv[0] = "c:/Users/jches/Documents/Programming/MSc Computing/Intro to C++/Coursework #2/main.exe";
    // argv[1] = "reflectors/I.rf";
    // argv[2] = "rotors/II.rot";
    // argc = 3;

    // Plugboard, but no rotor - invalid
    // argv[0] = "c:/Users/jches/Documents/Programming/MSc Computing/Intro to C++/Coursework #2/main.exe";
    // argv[1] = "plugboards/IV.pb";
    // argv[2] = "reflectors/I.rf";
    // argv[3] = "rotors/II.rot";
    // argc = 4;

    cout << "Have " << argc << " arguments:" << endl;

    for (size_t i = 0; i < argc; i++)
    {
        cout << argv[i] << endl;
    }

    // Initialise vectors to store inputs
    vector<string> plugboardInput;
    vector<string> reflectorInput;
    vector<string> rotorsInput[10];
    vector<string> rotorPosInput;

    // Check if Plugboard was supplied, if not default to the standard mapping
    string plugboardTest = argv[1];
    if (!plugboardSupplied(plugboardTest))
    {
        cout << "Plugboard not supplied, defaulting to standard mapping" << endl;
        for (int i = 0; i < 26; i++)
        {
            plugboardInput.push_back(to_string(i));
            plugboardInput.push_back(to_string(i));
        }

        parseInputStrings(argv[1], reflectorInput);
        printArray(reflectorInput);

        for (int i = 0; i < argc - 4; i++)
        {
            parseInputStrings(argv[2 + i], rotorsInput[i]);
            printArray(rotorsInput[i]);
        }

        parseInputStrings(argv[argc - 1], rotorPosInput);
        printArray(rotorPosInput);
    }
    else
    {
        cout << "Plugboard provided, saving to variable" << endl;
        parseInputStrings(argv[1], plugboardInput);
        printArray(plugboardInput);

        parseInputStrings(argv[2], reflectorInput);
        printArray(reflectorInput);

        for (int i = 0; i < argc - 4; i++)
        {
            parseInputStrings(argv[3 + i], rotorsInput[i]);
            printArray(rotorsInput[i]);
        }

        parseInputStrings(argv[argc - 1], rotorPosInput);
        printArray(rotorPosInput);
    }

    // Check if rotor start positions are supplied, throw an error if not
    string rotorPosTest = argv[argc - 1];
    if (!rotorSupplied(rotorPosTest))
    {
        cout << "Invalid rotor configuration" << endl;
        return INSUFFICIENT_NUMBER_OF_PARAMETERS;
    }
    else
    {
        cout << "Valid rotor configuration" << endl;
    }

    // Turn this into an Enigma Machine object for managing the while loop for inputting?
    // Initialise variable for storing encrypted letter
    int val;
    vector<Rotor> rotors;
    Plugboard plugboard;
    InputSwitches inputSwitches;
    // Rotor rotor;
    // if (rotor.initialiseRotor(rotorsInput[0], 0, rotorPosInput[rotorPosInput.size() - 1]) != 0)
    // {
    //     return rotor.initialiseRotor(rotorsInput[0], 0, rotorPosInput[rotorPosInput.size() - 1]);
    // }
    plugboard.initialisePlugboard(plugboardInput);
    for (int i = 0; i < rotorPosInput.size(); i++)
    {
        Rotor rotor;
        rotor.initialiseRotor(rotorsInput[i], i, rotorPosInput[i]);
        rotors.push_back(rotor);
    }

    // rotor.initialiseRotor(rotorsInput[0], 0, rotorPosInput[rotorPosInput.size() - 1]);
    inputSwitches.readInput(val);
    plugboard.swapLetter(val, val);

    for (int i = rotorPosInput.size() - 1; i >= 0; i--)
    {
        int tempVal = val;
        if (rotors[i].rotorNum == rotorPosInput.size() - 1)
        {
            cout << "Encrypting through first rotor, rotating first" << endl;
            rotors[i].rotateRotor();
        }

        if (rotors[i].checkNotch() && i != 0)
        {
            cout << "Rotated onto a notch, rotating rotor to the left" << endl;
            rotors[i - 1].rotateRotor();
        }
        rotors[i].mapNumber(val);
        cout << "Rotor " << i << " encrypted " << tempVal << " to " << val << endl;
    }

    // Logic for using rotors here.

    // Rotate rotor to the left (ID -1) if checkNotch returns true;
    return NO_ERROR;
}

int parseInputStrings(char arrayIn[], vector<string> &arrayOut)
{
    // Function to read in the arguments
    // Pass a ref to the arrays in main
    // Read the file name of the dir so we know what they are
    // Create an in stream and read the file contents into an array for each file name
    cout << "------" << endl;
    cout << "Reading array in: ";
    cout << arrayIn << endl;

    // Open an input file stream
    ifstream input;
    input.open(arrayIn);

    // Create variables to store the character, and each set of characters that complete the number
    char ch;
    string num;

    if (input.fail())
    {
        cerr << "Cannot open file" << endl;
        return 11;
    }

    int i = 0;
    while (!input.fail())
    {
        input.get(ch);
        // Run checkNumeric first, if false return the error code.

        // If it is not a space or end of file, copy the numbers to a temp string
        if (ch != ' ' && ch != '\n')
        {
            num += ch;
        }
        // Conver the temp string to an int and store it in the array
        else if (ch != '\n')
        {
            arrayOut.push_back(num);
            num = "";
            i++;
        }
        else if (ch == '\n')
        {
            arrayOut.push_back(num);
            break;
        }
    }

    input.close();

    printArray(arrayOut);

    return 0;
}

void printArray(vector<string> &array)
{
    // Check array
    cout << "Array is: ";
    for (size_t i = 0; i < array.size(); i++)
    {
        cout << array[i] << ' ';
    }
    cout << endl;
}

void printArray(vector<int> &array)
{
    // Check array
    cout << "Array is: ";
    for (size_t i = 0; i < array.size(); i++)
    {
        cout << array[i] << ' ';
    }
    cout << endl;
}

bool plugboardSupplied(string plugboardTest)
{
    if (plugboardTest.back() == 'b')
    {
        cout << "Plugboard supplied" << endl;
        return true;
    }
    else
    {
        return false;
    }
}

bool rotorSupplied(string rotorPosTest)
{
    if (rotorPosTest.back() == 's')
    {
        cout << "Rotor Starting Positions Supplied" << endl;
        return true;
    }
    else
    {
        return false;
    }
}

bool isNumeric(string ch)
{
    try
    {
        int num = stoi(ch);
        return true;
    }
    catch (...)
    {
        return false;
    }
}

/* This function checks if the input is in the range of 0-25 */
bool isValidNum(int num)
{
    if (num >= 0 || num <= 25)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isInArray(int n, vector<int> array)
{
    for (int i = 0; i < array.size(); i++)
    {
        if (n == array[i])
        {
            return true;
        }
    }
    return false;
}

bool isInArray(int n, vector<int> array, int &arrayPosition)
{
    for (int i = 0; i < array.size(); i++)
    {
        if (n == array[i])
        {
            arrayPosition = i;
            return true;
        }
    }
    return false;
}

bool isValidLen(int n, vector<int> array)
{
    if (array.size() == n)
        return true;

    else
        return false;
}