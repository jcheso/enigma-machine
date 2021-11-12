#include <iostream>
#include "outputBoard.h"
using namespace std;

OutputBoard::OutputBoard()
{
    char outputLetter;
}

/* This method takes a number and returns the corresponding character */
void OutputBoard::mapNum2Letter(int num, char ch)
{
    ch = static_cast<char>(num + 65);
    cout << ch;
}
