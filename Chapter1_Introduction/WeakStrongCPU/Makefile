CC = g++
CFLAGS = -std=c++17

WeakStrongCPU : WeakStrongCPU.o
	$(CC) $(CFLAGS) -o WeakStrongCPU WeakStrongCPU.o

WeakStrongCPU.o : WeakStrongCPU.cpp
	$(CC) $(CFLAGS) -c WeakStrongCPU.cpp

clean :
	rm -f WeakStrongCPU
	rm -f *.o
