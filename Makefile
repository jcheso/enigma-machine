all: enigma

enigma: main.o helper.o
	g++ -g main.o helper.o -o enigma

main.o: main.cpp helper.h
	g++ -Wall -g -c main.cpp

helper.o: helper.cpp helper.h
	g++ -Wall -g -c helper.cpp helper.h

clean:
	rm -f *.o enigma