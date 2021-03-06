#include <iostream>
#include <string>
#include <vector>
#include "helper.h"
#include "errors.h"
#include "plugboard.h"
using namespace std;

Plugboard::Plugboard() {}

void Plugboard::fillArray(vector<int> &array1, vector<int> &array2, int arrSize)
{
    int num2add;
    // Iterate from 0 to number of letters missing from Alphabet
    for (int i = 0; i < (26 - (arrSize * 2)); i++)
    {
        // Iterate from 0 - 25 and check if the value is in the input array
        for (int j = 0; j < 26; j++)
        {
            // If not in array, push value to input and output arrays.
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

void Plugboard::swapLetter(int &output)
{
    int input = output;
    int arrayPosition;
    // Find which array the letter is in and swap accordingly.
    if (isInArray(input, array1, arrayPosition))
        output = array2[arrayPosition];
    else if (isInArray(input, array2, arrayPosition))
        output = array1[arrayPosition];
}

void Plugboard::generateDefaultPlugboard()
{
    for (int i = 0; i < 26; i++)
    {
        array1.push_back(i);
        array2.push_back(i);
    }
}