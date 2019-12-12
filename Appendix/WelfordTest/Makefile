CC = g++
CFLAGS = -std=c++17

WelfordTest : WelfordTest.o Welford.o
	$(CC) $(CFLAGS) -o WelfordTest WelfordTest.o Welford.o

WelfordTest.o : WelfordTest.cpp Welford.h ReturnValues.h
	$(CC) $(CFLAGS) -c WelfordTest.cpp

clean :
	rm -f *.o
	rm -f WelfordTest

