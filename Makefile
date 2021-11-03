all: enigma

enigma: main.o
	g++ -g main.o -o enigma

# main.o: main.cpp errors.h
# 	g++ -Wall -g -c main.cpp

# erorrs.o: errors.h
# 	g++ -Wall -g -c errors.h

clean:
	rm -f *.o enigma