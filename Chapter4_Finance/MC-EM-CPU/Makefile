CC = g++
CFLAGS = -std=c++17
COMMON = ../Common/*.o

MC-EM-CPU : MC-EM-CPU.o Simulate-MC-EM-CPU.o
	$(CC) $(CFLAGS) -o MC-EM-CPU MC-EM-CPU.o $(COMMON)

MC-EM-CPU.o : MC-EM-CPU.cpp
	$(CC) $(CFLAGS) -c MC-EM-CPU.cpp

Simulate-MC-EM-CPU.o : Simulate-MC-EM-CPU.cpp
	$(CC) $(CFLAGS) -c Simulate-MC-EM-CPU.cpp


clean :
	rm -f MC-EM-CPU
	rm -f *.o
