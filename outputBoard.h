#ifndef OUTPUT_BOARD_H
#define OUTPUT_BOARD_H
#include <iostream>
using namespace std;

class OutputBoard
{
private:
    // Define any private variables and methods here
    char outputLetter;
    // Define any public variables and methods here
public:
    OutputBoard();
    /* This method takes a number and outputs the corresponding character */
    void mapNum2Letter(int num, char ch);
};
#endif