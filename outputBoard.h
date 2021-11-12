#ifndef OUTPUT_BOARD_H
#define OUTPUT_BOARD_H
#include <iostream>
using namespace std;

/* Probably not necessary as an Object but keeps the Enigma components distinct */
class OutputBoard
{
private:
public:
    OutputBoard();
    /* This method takes a number and outputs the corresponding character */
    void outputLetter(int num);
};
#endif