#ifndef REFLECTOR_H
#define REFLECTOR_H
#include <iostream>
#include <string>
#include <vector>
#include "helper.h"
#include "errors.h"
using namespace std;

class Reflector
{
private:
    vector<int> array1;
    vector<int> array2;

public:
    Reflector();
    /* This method initialises a reflector from a provided config file */
    int initialiseReflector(vector<string> config);
    /* This function takes the number and finds which array it's in, then returns its corresponding value */
    void reflectNumber(int &output);
};
#endif