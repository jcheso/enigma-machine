#include <iostream>
#include "inputSwitches.h"
#include "helper.h"
#include "errors.h"
using namespace std;

InputSwitches::InputSwitches()
{
}

int InputSwitches::readInput(int &num)
{
    char ch;
    cin >> ws;
    cin >> ch;
    num = ch - 65;
    if (!isValidNum(num))
    {
        cerr << ch << " is not a valid input character (input characters must be upper case letters A-Z)!" << endl;
        throw(INVALID_INPUT_CHARACTER);
    }
    return NO_ERROR;
}