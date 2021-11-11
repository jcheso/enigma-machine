all: enigma

enigma: main.o helper.o inputSwitches.o plugboard.o
	g++ -g main.o helper.o inputSwitches.o plugboard.o -o enigma

main.o: main.cpp helper.h
	g++ -Wall -g -c main.cpp

helper.o: helper.cpp helper.h
	g++ -Wall -g -c helper.cpp helper.h

inputSwitches.o: inputSwitches.cpp inputSwitches.h
	g++ -Wall -g -c inputSwitches.cpp inputSwitches.h

plugboard.o: plugboard.cpp plugboard.h
	g++ -Wall -g -c plugboard.cpp plugboard.h

clean:
	rm -f *.o enigma