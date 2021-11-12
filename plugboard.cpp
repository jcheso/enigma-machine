#include <iostream>
#include <string>
#include <vector>
#include "helper.h"
#include "errors.h"
#include "plugboard.h"
using namespace std;

Plugboard::Plugboard()
{
    vector<int> array1;
    vector<int> array2;
    vector<string> plugboardInput;
}

/* This method fills the remainder of the plugboard with the missing characters */
void Plugboard::fillArray(vector<int> &array1, vector<int> &array2, int arrSize)
{
    int num2add;
    // Iterate from 0 to 25 and check if the value is in the input array
    for (size_t i = 0; i < (26 - (arrSize * 2)); i++)
    {
        for (size_t j = 0; j < 26; j++)
        {
            // If not in index, append value to input and output arrays.
            if (!isInArray(j, array1) && !isInArray(j, array2))
            {
                num2add = j;
                break;
            }
        }
        array1.push_back(num2add);
        array2.push_back(num2add);
    }
};

/* This method takes in a config file and initialises the plugboard array, if no array is
provided it will initialise a default 1 to 1 plugboard */
int Plugboard::initialisePlugboard(vector<string> config)
{
    if (config.size() > 0)
    {
        int num;
        // Check if plugboard is even and not over 26 chars
        if ((config.size() % 2 != 0) || (config.size() > 26))
        {
            cerr << "Incorrect number of parameters in plugboard file plugboard.pb" << endl;
            throw(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
        }
        for (size_t i = 0; i < config.size(); i++)
        {
            // Check isNumeric() & convert to int if true. Return error code if false
            if (isNumeric(config[i]))
                num = stoi(config[i]);
            else
            {
                cerr << "Non-numeric character in plugboard file plugboard.pb" << endl;
                throw(NON_NUMERIC_CHARACTER);
            }
            // Check isValidNum() and return error code if false
            if (!isValidNum(num))
            {
                cerr << "Invalid index provided at" << num << endl;
                throw(INVALID_INDEX);
            }
            // Check if it isInArray(). If not, split the pairs into their arrays
            if (!isInArray(num, array2) && !isInArray(num, array1))
            {
                if (i % 2 == 0)
                    array1.push_back(num);
                else
                    array2.push_back(num);
            }
            else
            {
                cerr << "Error in plugboard config" << endl;
                throw(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
            }
        }
    }

    // Check if length of input array is less than 26, if so run fillArray on both arrays to map remaining numbers
    if (config.size() < 26)
        fillArray(array1, array2, array2.size());
    return NO_ERROR;
}

/* This class method takes in an input and swaps it to the correct output */
void Plugboard::swapLetter(int input, int &output)
{
    int arrayPosition;
    if (isInArray(input, array1, arrayPosition))
        output = array2[arrayPosition];
    else if (isInArray(input, array2, arrayPosition))
        output = array1[arrayPosition];
}

void Plugboard::generateDefaultPlugboard()
{
    for (size_t i = 0; i < 26; i++)
    {
        array1.push_back(i);
        array2.push_back(i);
    }
}