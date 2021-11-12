#ifndef ROTOR_H
#define ROTOR_H
#include <iostream>
#include <string>
#include <vector>
#include "helper.h"
#include "errors.h"
using namespace std;

/* This class models a Rotor */
class Rotor
{
private:
    vector<int> rotorMap;
    vector<int> notches;
    int startPosition;
    int num;
    int index;
    int rotations;
    /* This method gets the start position of the rotor from the config provided */
    int getStartPosition(string config);
    /* This method sets the start position of the rotor */
    void setStartPosition();

public:
    Rotor();
    bool activatedNotch;
    /* This method initialises a rotor from a provided config file */
    int initialiseRotor(vector<string> config, string rotorPosInput);
    /* This method rotates the rotor*/
    void rotateRotor();
    /* This method maps the input number to the output number */
    void mapNumber(int &num, bool reflected);
    /* This method checks if the notch is at 12 o'clock */
    bool checkNotch();
};
#endif