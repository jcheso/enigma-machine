#ifndef INPUT_SWITCHES_H
#define INPUT_SWITCHES_H
#include <iostream>
#include "helper.h"
#include "errors.h"
using namespace std;

/* This class models the Input Switches */
class InputSwitches
{
private:
    char ch;

public:
    InputSwitches();
    /* This method reads in a char and updates a reference variable to an int corresponding to the position in the Alphabet
     * If an error is encountered with the input it will return the error code.
     */
    int readInput(int &num);
};

#endif