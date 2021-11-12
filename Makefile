all: enigma

enigma: main.o helper.o inputSwitches.o plugboard.o rotor.o reflector.o outputBoard.o
	g++ -g main.o helper.o inputSwitches.o plugboard.o rotor.o reflector.o outputBoard.o -o enigma

main.o: main.cpp helper.h
	g++ -Wall -g -c main.cpp

helper.o: helper.cpp helper.h
	g++ -Wall -g -c helper.cpp helper.h

inputSwitches.o: inputSwitches.cpp inputSwitches.h
	g++ -Wall -g -c inputSwitches.cpp inputSwitches.h

plugboard.o: plugboard.cpp plugboard.h
	g++ -Wall -g -c plugboard.cpp plugboard.h

rotor.o: rotor.cpp rotor.h
	g++ -Wall -g -c rotor.cpp rotor.h

reflector.o: reflector.cpp reflector.h
	g++ -Wall -g -c reflector.cpp reflector.h

outputBoard.o: outputBoard.cpp outputBoard.h
	g++ -Wall -g -c outputBoard.cpp outputBoard.h

clean:
	rm -f *.o enigma