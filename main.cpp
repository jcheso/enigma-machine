#include <iostream>
#include <fstream>
#include "errors.h"
#include <string>
#include <vector>
using namespace std;

/* This function takes an input string and assigns the contents to an array - Save as vector of strings instead of int?*/
int parseInputStrings(char array[], vector<int> &arrayOut);
/* This function takes the initial argument and if a plugboard was provided */
bool checkPlugboardSupplied(int argc, char **argv);
/* This function takes an array and prints it */
void printArray(vector<int> &array);

/* This function calculates the modulus and returns the new integer */
int takeModulus(int n);
/* ---- ERROR CHECKS - RETURN THE CORRECT ERROR CODE WITHIN THE CLASS */
/* This function checks if the input is numeric */
int isNumeric(char ch);
/* This function checks if the input is in the range of 0-25 */
int isValidNum(char ch);
/* This function checks if the array is the expected length */
int isValidLen(int n, vector<int> array);
/* This function checks if the value is already in the array */
int isInArray(int n, vector<int> array);

/* This class models the Input Switches */
class InputSwitches
{
    // This vector keeps track of all the input characters
    string input;

public:
    // Define any public variables and methods here
    /* This method reads in a character and returns an integer corresponding to it's position in the Alphabet */
    int readInput(char ch)
    {
        // Add ch to string for record keeping
        // Ignore whitespace
        // Convert char to int
        // Check if input isValidNum
        // Return the int
    }
};

/* This class models the Plugboard */
class Plugboard
{
    // Define any private variables and methods here
    vector<int> inputArray;
    vector<int> outputArray;
    /* This method fills the remainder of the plugboard with the missing characters */
    void fillArray(){
        // Iterate from 0 to 25 and check if the value is in the input array
        // If not in index, append value to input and output arrays.
    };
    // Define any public variables and methods here
public:
    /* This method takes in a config file and initialises the plugboard array, if no array is
    provided it will initialise a default 1 to 1 plugboard */
    int initialisePlugboard(vector<string> *config)
    {
        // If null ptr, then return a default plugboard
        // If not a null ptr, initialise the board in a for loop
        // **Start Loop**
        // Check isNumeric()
        // Check isValidNum()
        // Check isInArray()
        // If value is odd - assign to input array
        // If value is even - assign to output array
        // **End Loop**
        // Check if length of input array is less than 25, if so run fillArray on both arrays
        // Check isValidLen()
        // Return 0 if no error
    }

    /* This class method takes in an input and swaps it to the correct output */
    int swapLetter(int input, int output)
    {
        // Get the index of the input in the inputArray
        // Return the value at that index in the outputArray
    }
};

/* This class models a Rotor */
class Rotor
{
    // Define any private variables and methods here
    vector<int> rotorMap;
    vector<int> originalRotorMap;
    vector<int> notches;
    bool hasNotch;
    int rotations = 0;
    int startPosition;
    int mappedNumber;
    // Need a constructor to set the rotorNum on initialisation
    int rotorNum;
    /* This method checks if the notch is at 12 o'clock */
    bool checkNotch()
    {
        // Iterate through notches
        // Check if the current rotation is at the notch
        // notchStartPosition = originalRotorMap[notch]
        // currentNotchPosition = notchStartPosition + rotations
        // If mod(notchStartPosition + Rotations) = 0 then
        // Rotate rotor to the left (ID -1)
    }

    /* This method sets the start position of the rotor */
    int setStartPosition()
    {
        // Calculate the required rotations as Modulus of (26-rotorMap[startPosition] + startPosition)
        // Call rotateRotorRight with the number of rotations required to set the correct start position
    }
    // Define any public variables and methods here
public:
    /* This method initialises a rotor from a provided config file */
    int initialiseRotor(vector<string> config)
    {
        // Initialise an iterator
        // Iterate through the array up to 25 digits
        // Check isInArray(rotorMap)
        // Check isNumeric()
        // Check isNumValid()
        // Append to rotorMap
        // Check isValidLen(rotorMap)
        // Check len of config to see if there are notches, if no notches set to false; else:
        // Iterate through the array from 26-len(array)
        // Check isInArray(notches)
        // Check isNumeric()
        // Check isNumValid()
        // Append to notches
        // Call getStartPosition()
        // Call setStartPosition()
    }
    /* This method gets the start position of the rotor from the config provided */
    int getStartPosition(vector<int> config)
    {
        // Get the rotor start position corresponding to the rotorNum
        // If does not exist, exit with NO_ROTOR_STARTING_POSITION
        // Check isNumeric()
        // Check isValidNum()
        // Set startPosition to value
    }
    /* This method rotates the rotor specified*/
    void rotateRotor(int rotorNum)
    {
        // Shift rotorMap array to the right by one
    }
    /* This method maps the input number to the output number */
    int mapNumber(int num)
    {
        // If it has a notch
        // checkNotch()
        // If it is rotor 1, rotate rotor (does this happen if rotates from a notch as well?)
        // return the rotorMap[num] as the mappedNumber
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
    // Need to change this to check the if a plugboard was supplied first, then check num parameters.
    // Check how many rotors there are. Throw an error if no rotors are supplied.
    if ((argc - 4) == 0)
    {
        return INSUFFICIENT_NUMBER_OF_PARAMETERS;
    }
    else
    {
        cout << "Using " << (argc - 4) << " rotors" << endl;
    }

    // Set up test variables for debugging
    char testPlugboard[] = "plugboards/IV.pb";
    char testReflectors[] = "reflectors/I.rf";
    char testRotor[] = "rotors/II.rot";
    char testRotorPos[] = "rotors/I.pos";

    // Initialise arrays to store our config files - change to array lib?
    vector<int> plugboard[25];
    vector<int> reflector[25];
    vector<int> rotors[10][25];

    cout << "Have " << argc << " arguments:" << endl;

    for (size_t i = 0; i < argc; i++)
    {
        cout << argv[i] << endl;
    }

    // First input is always a plugboard
    // Second input is always a reflector
    // 3 - Argc is rotors
    parseInputStrings(argv[1], plugboard[25]);
    printArray(plugboard[25]);
    parseInputStrings(argv[2], reflector[25]);
    printArray(reflector[25]);

    return 0;
}

int parseInputStrings(char arrayIn[], vector<int> &arrayOut)
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
    string char2num;

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
            char2num += ch;
        }
        // Conver the temp string to an int and store it in the array
        else if (ch != '\n')
        {
            arrayOut.push_back(stoi(char2num));
            char2num = "";
            i++;
        }
        else if (ch == '\n')
        {
            arrayOut.push_back(stoi(char2num));
            break;
        }
    }

    input.close();

    printArray(arrayOut);

    return 0;
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
