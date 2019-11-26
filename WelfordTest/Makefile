CC = g++
CFLAGS = -std=c++17
COMMON = ../Common
INCLUDE = -I$(COMMON)

WelfordTest : WelfordTest.o $(COMMON)/Welford.o
	$(CC) $(CFLAGS) $(INCLUDE) -o WelfordTest WelfordTest.o $(COMMON)/Welford.o

WelfordTest.o : WelfordTest.cpp $(COMMON)/Welford.h $(COMMON)/ReturnValues.h
	$(CC) $(CFLAGS) $(INCLUDE) -c WelfordTest.cpp

clean :
	rm -f *.o
	rm -f WelfordTest

