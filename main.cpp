#include <iostream>
#include <fstream>
#include "errors.h"
#include <string>
#include <vector>
using namespace std;

/* This function takes the command line input and assigns the contents to an array */
int readInputs(int argc, char array[], vector<int> &arrayOut);
void printArray(vector<int> &array);
void checkRotorCount(int argc);

int main(int argc, char **argv)
{
    // Check how many rotors there are. Throw an error if no rotors are supplied.
    if ((argc - 3) == 0)
    {
        return INSUFFICIENT_NUMBER_OF_PARAMETERS;
    }
    else
    {
        cout << "Using " << (argc - 3) << " rotors" << endl;
    }

    // Set up test variables for debugging
    char testPlugboard[] = "plugboards/IV.pb";
    char testReflectors[] = "reflectors/I.rf";
    char testRotor1[] = "rotors\II.rot";
    char testRotor2[] = "rotors/I.pos";

    // Initialise arrays to store our config files
    vector<int> plugboard;
    vector<int> reflector;

    vector<int> rotors[10][25];

    cout << "Have " << argc << " arguments:" << endl;

    for (size_t i = 0; i < argc; i++)
    {
        cout << argv[i] << endl;
    }

    // First input is always a plugboard
    // Second input is always a reflector
    // 3 - Argc is rotors
    readInputs(1, argv[1], plugboard);
    printArray(plugboard);
    readInputs(1, argv[2], reflector);
    printArray(reflector);

    return 0;
}

int readInputs(int argc, char arrayIn[], vector<int> &arrayOut)
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

void checkRotorCount(int argc)
{
}
