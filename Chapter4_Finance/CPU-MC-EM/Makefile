CC = module load gcc/6.2.0 ; g++
CCFlags = -std=c++17

all : CPU-MC-EM

CPU-MC-EM : CPU-MC-EM.o MonteCarlo.o
	$(CC) $(CFLAGS) -o CPU-MC-EM CPU-MC-EM.o MonteCarlo.o

CPU-MC-EM.o : CPU-MC-EM.cpp MonteCarlo.h
	$(CC) -c CPU-MC-EM.cpp

MonteCarlo.o : MonteCarlo.cpp MonteCarlo.h
	$(CC) -c MonteCarlo.cpp


clean:
	rm -f *.o CPU-MC-EM


.PHONY: clean all
		