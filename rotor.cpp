#include <iostream>
#include <string>
#include <vector>
#include "helper.h"
#include "errors.h"
#include "rotor.h"
using namespace std;

Rotor::Rotor() {}

int Rotor::getStartPosition(string config)
{
    if (!isNumeric(config))
    {
        cerr << "Non-numeric character in rotor positions file rotor.pos" << endl;
        throw(NON_NUMERIC_CHARACTER);
    }
    startPosition = stoi(config);
    if (!isValidNum(startPosition))
    {
        cerr << "Invalid index provided" << endl;
        throw(INVALID_INDEX);
    }
    return NO_ERROR;
}

void Rotor::setStartPosition()
{
    for (int i = 0; i < startPosition; i++)
        rotateRotor();
}

/* This method initialises a rotor from a provided config file */
int Rotor::initialiseRotor(vector<string> config, string rotorPosInput)
{
    // Check if length is valid
    if (config.size() < 26)
    {
        cerr << "Not all inputs mapped in rotor file: rotor.rot" << endl;
        throw(INVALID_ROTOR_MAPPING);
    }
    for (size_t i = 0; i < config.size(); i++)
    {
        int num;
        // Check isNumeric() & convert to int if true. Return error code if false
        if (isNumeric(config[i]))
            num = stoi(config[i]);
        else
        {
            cerr << "Non-numeric character for mapping in rotor file rotor.rot" << endl;
            throw(NON_NUMERIC_CHARACTER);
        }
        // Check isValidNum() and return error code if false
        if (!isValidNum(num))
        {
            cerr << "Invalid index provided" << endl;
            throw(INVALID_INDEX);
        }
        int index;
        if (isInArray(num, rotorMap, index) && i < 26)
        {
            cerr << "Invalid mapping of input " << i << " to output " << num << " (output " << num << " is already mapped to from input " << index << ") in rotor file: rotor.rot" << endl;
            throw(INVALID_ROTOR_MAPPING);
        }
        // Add to rotorMap if its in the first 25 digits
        if (i < 26)
            rotorMap.push_back(num);
        // Add to notches if its past the first 25 digits and set this rotor to have notches
        if (i >= 26)
        {
            notches.push_back(num);
        }
    }
    rotations = 0;
    getStartPosition(rotorPosInput);
    setStartPosition();
    return NO_ERROR;
}
void Rotor::rotateRotor()
{
    // Shift rotorMap array to the left by one and add one to number to account for rotation
    int first = rotorMap[0] - 1;
    // If goes past A set to Z
    if (first < 0)
        first = 25;
    for (size_t i = 0; i < rotorMap.size(); i++)
    {
        rotorMap[i] = (rotorMap[i + 1] - 1);
        if (rotorMap[i] < 0)
            rotorMap[i] = 25;
    }
    rotorMap[rotorMap.size() - 1] = first;
    rotations++;
}
void Rotor::mapNumber(int &num, bool reflected)
{
    if (!reflected)
        num = rotorMap[num];
    else
        isInArray(num, rotorMap, num);
}
bool Rotor::checkNotch()
{
    // Iterate through notches & check if the current rotation is at the notch
    for (size_t i = 0; i < notches.size(); i++)
    {
        if (rotations == notches[i])
            return true;
    }
    return false;
}
