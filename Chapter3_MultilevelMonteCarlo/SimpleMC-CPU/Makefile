CC = g++
CFLAGS = -std=c++17


simplemc : simplemc.o
	$(CC) -o simplemc simplemc.o

simplemc.o : simplemc.cpp
	$(CC) -c simplemc.cpp

clean : 
	rm -f simplemc
	rm -f *.o

