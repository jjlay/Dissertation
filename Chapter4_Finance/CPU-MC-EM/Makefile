CC = module load gcc/6.2.0 ; g++
CFLAGS = -std=c++17
INCLUDEDIRS = ../Common/

all : CPU-MC-EM

CPU-MC-EM : CPU-MC-EM.o MonteCarlo.o 
	$(CC) $(CFLAGS) -o CPU-MC-EM CPU-MC-EM.o MonteCarlo.o ../Common/parseCommandLine.o 

CPU-MC-EM.o : CPU-MC-EM.cpp MonteCarlo.h
	$(CC) $(CFLAGS)  -c CPU-MC-EM.cpp -I$(INCLUDEDIRS)

MonteCarlo.o : MonteCarlo.cpp MonteCarlo.h
	$(CC) $(CFLAGS) -c MonteCarlo.cpp -I$(INCLUDEDIRS)


clean:
	rm -f *.o CPU-MC-EM


.PHONY: clean all
		
