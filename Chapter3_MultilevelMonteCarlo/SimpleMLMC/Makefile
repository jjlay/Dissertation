CC = g++
CFLAGS = -std=c++17

SimpleMLMC : SimpleMLMC.o
	$(CC) $(CFLAGS) -o SimpleMLMC SimpleMLMC.o

SimpleMLMC.o : SimpleMLMC.cpp ReturnValues.h
	$(CC) $(CFLAGS) -c SimpleMLMC.cpp

clean :
	rm -f SimpleMLMC
	rm -f *.o
