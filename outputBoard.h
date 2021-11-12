#ifndef OUTPUT_BOARD_H
#define OUTPUT_BOARD_H
#include <iostream>
using namespace std;

class OutputBoard
{
private:
public:
    OutputBoard();
    /* This method takes a number and outputs the corresponding character */
    void mapNum2Letter(int num, char ch);
};
#endif