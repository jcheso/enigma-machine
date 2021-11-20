#include <iostream>
#include "outputBoard.h"
using namespace std;

OutputBoard::OutputBoard() {}
void OutputBoard::outputLetter(int num)
{
    char ch = num + 'A';
    cout << ch;
}
