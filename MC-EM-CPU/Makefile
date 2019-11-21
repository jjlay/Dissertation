CC = g++
CFLAGS = -std=c++17

MC-EM-CPU : MC-EM-CPU.o
	$(CC) $(CFLAGS) -o MC-EM-CPU MC-EM-CPU.o

MC-EM-CPU.o : MC-EM-CPU.cpp
	$(CC) $(CFLAGS) -c MC-EM-CPU MC-EM-CPU.cpp

clean :
	rm -f MC-EM-CPU
	rm -f *.o