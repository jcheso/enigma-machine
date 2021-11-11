#ifndef PLUGBOARD_H
#define PLUGBOARD_H
#include <iostream>
#include <string>
#include <vector>
#include "helper.h"
#include "errors.h"
using namespace std;
class Plugboard
{
private:
    vector<int> array1;
    vector<int> array2;

    /* This method fills the remainder of the plugboard with the missing characters */
    void fillArray(vector<int> &array1, vector<int> &array2, int arrSize);

public:
    bool usingDefaultPlugboard;
    Plugboard();
    /* This method takes in a config file and initialises the plugboard array, if no array is
    provided it will initialise a default 1 to 1 plugboard */
    int initialisePlugboard(vector<string> config);
    /* This class method takes in an input and swaps it to the correct output */
    void swapLetter(int input, int &output);
};
#endif