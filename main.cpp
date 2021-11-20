#include "enigma.h"
using namespace std;

int main(int argc, char **argv)
{
    Enigma enigma(argc, argv);
    try
    {
        enigma.readConfigFiles();
        enigma.initialiseMachine();
        enigma.encryptMessage();
    }
    catch (int error)
    {
        return error;
    }
    return NO_ERROR;
}
