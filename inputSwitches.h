#ifndef INPUT_SWITCHES_H
#define INPUT_SWITCHES_H
#include <iostream>
#include "helper.h"
#include "errors.h"
using namespace std;

/* This class models the Input Switches */
class InputSwitches
{

public:
    InputSwitches();
    /* This method reads in a char and returns an int corresponding to the position in the Alphabet */
    int readInput(int &num);
};

#endif