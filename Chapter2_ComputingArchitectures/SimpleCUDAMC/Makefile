CC = nvcc
CFLAGS = -std=c++17

SimpleCUDAMC : SimpleCUDAMC.o
	$(CC) $(CFLAGS) -o SimpleCUDAMC SimpleCUDAMC.o

SimpleCUDAMC.o : SimpleCUDAMC.cpp ReturnValues.h
	$(CC) $(CFLAGS) -c SimpleCUDAMC.cpp

clean :
	rm -f SimpleCUDAMC
	rm -f *.o
