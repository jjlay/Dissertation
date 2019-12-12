CC = g++
CFLAGS = -std=c++17

MLMC-EM-CPU : MLMC-EM-CPU.o
	$(CC) $(CFLAGS) -o MLMC-EM-CPU MLMC-EM-CPU.o

MLMC-EM-CPU.o : MLMC-EM-CPU.cpp
	$(CC) $(CFLAGS) -c MLMC-EM-CPU MLMC-EM-CPU.cpp

clean :
	rm -f MLMC-EM-CPU
	rm -f *.o

