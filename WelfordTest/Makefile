CC = g++
CFLAGS = -std=c++17


WelfordTest : WelfordTest.o ../Common/Welford.o
	$(CC) $(CFLAGS) -o WelfordTest WelfordTest.o ../Common/Welford.o

WelfordTest.o : WelfordTest.cpp ../Common/Welford.h ../Common/ReturnValues.h
	$(CC) $(CFLAGS) -c WelfordTest.cpp

clean :
	rm -f *.o
	rm -f WelfordTest

