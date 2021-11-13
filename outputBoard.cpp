#include <iostream>
#include "outputBoard.h"
using namespace std;

OutputBoard::OutputBoard() {}
void OutputBoard::outputLetter(int num)
{
    char ch;
    ch = static_cast<char>(num + 65);
    cout << ch;
}
