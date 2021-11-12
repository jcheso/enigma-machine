#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "helper.h"
#include "errors.h"
using namespace std;

int parseInputStrings(char arrayIn[], vector<string> &arrayOut)
{
    ifstream input;
    input.open(arrayIn);
    string stringOfNums;
    if (input.fail())
    {
        cerr << "Cannot open file: " << arrayIn << endl;
        throw(ERROR_OPENING_CONFIGURATION_FILE);
    }
    while (!input.fail())
    {
        char ch = ' ';
        input.get(ch);
        // Push to string if double digit
        if (ch != ' ' && ch != '\n')
            stringOfNums += ch;
        // Push to string if single digit
        else if (ch != '\n' && stringOfNums[0] != '\000')
        {
            arrayOut.push_back(stringOfNums);
            stringOfNums = "";
        }
        // If last element push to string if it's a digit, then break
        else if (ch == '\n' && stringOfNums[0] != '\000')
        {
            arrayOut.push_back(stringOfNums);
            break;
        }
        else
            break;
    }
    input.close();
    return NO_ERROR;
}

bool isFileSupplied(string filename, char lastChar)
{
    if (filename.back() == lastChar)
        return true;
    else
        return false;
}

bool isNumeric(string ch)
{
    try
    {
        for (size_t i = 0; i < ch.size(); i++)
        {
            string tempString;
            tempString = ch[i];
            int num = stoi(tempString);
        }
        return true;
    }
    catch (...)
    {
        return false;
    }
}

bool isValidNum(int num)
{
    if (num > -1 && num < 26)
        return true;
    else
        return false;
}

bool isInArray(int n, vector<int> array)
{
    for (size_t i = 0; i < array.size(); i++)
    {
        if (n == array[i])
            return true;
    }
    return false;
}

bool isInArray(int n, vector<int> array, int &arrayPosition)
{
    for (size_t i = 0; i < array.size(); i++)
    {
        if (n == array[i])
        {
            arrayPosition = i;
            return true;
        }
    }
    return false;
}

bool checkCorrectParameters(int argc, char **argv)
{
    // If a plugboard is supplied, check if there is at least one reflector, rotor and rotor position
    if (isFileSupplied(argv[1], 'b') && (!isFileSupplied(argv[2], 'f') || !isFileSupplied(argv[3], 't') || !isFileSupplied(argv[argc - 1], 's')))
        return false;

    // If a plugboard is not supplied, check if there is at least one reflector, rotor and rotor position
    else if (!isFileSupplied(argv[1], 'b') && (!isFileSupplied(argv[1], 'f') || !isFileSupplied(argv[2], 't') || !isFileSupplied(argv[argc - 1], 's')))
        return false;

    return true;
}