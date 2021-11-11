all: enigma

enigma: main.o helper.o inputSwitches.o
	g++ -g main.o helper.o inputSwitches.o -o enigma

main.o: main.cpp helper.h
	g++ -Wall -g -c main.cpp

helper.o: helper.cpp helper.h
	g++ -Wall -g -c helper.cpp helper.h

inputSwitches.o: inputSwitches.cpp inputSwitches.h
	g++ -Wall -g -c inputSwitches.cpp inputSwitches.h

clean:
	rm -f *.o enigma