#ifndef HELPER_H
#define HELPER_H
#include <string>
#include <vector>
using namespace std;

/* This function takes an input string and assigns the contents to an string vector for further processing later */
int parseInputStrings(char array[], vector<string> &arrayOut);

/* This function checks if a plugboard was provided */
bool plugboardSupplied(string plugboardTest);

/* This function checks if a rotor starting position was provided */
bool rotorSupplied(string rotorPosTest);

/* This function checks if the input is numeric */
bool isNumeric(string ch);

/* This function checks if the input is in the range of 0-25 */
bool isValidNum(int num);

/* This function checks if the array is the expected length */
bool isValidLen(int n, vector<int> array);

/* This function checks if the value is already in the array */
bool isInArray(int n, vector<int> array);

/* This function checks if the value is already in the array and returns the position */
bool isInArray(int n, vector<int> array, int &arrayPosition);

#endif