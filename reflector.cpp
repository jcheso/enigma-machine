#include <iostream>
#include <string>
#include <vector>
#include "helper.h"
#include "errors.h"
#include "reflector.h"
using namespace std;

Reflector::Reflector() {}

int Reflector::initialiseReflector(vector<string> config)
{
    int num;
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

    for (size_t i = 0; i < config.size(); i++)
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

void Reflector::reflectNumber(int &output)
{
    int input = output;
    int arrayPosition;
    // Find which array the letter is in and swap accordingly.
    if (isInArray(input, array1, arrayPosition))
        output = array2[arrayPosition];
    else if (isInArray(input, array2, arrayPosition))
        output = array1[arrayPosition];
}
