CC = nvcc
CFLAGS = -std=c++17


WeakStrongCUDA : WeakStrongCUDA.o
	nvcc -o WeakStrongCUDA WeakStrongCUDA.o

WeakStrongCUDA.o : WeakStrongCUDA.cu
	nvcc -c WeakStrongCUDA.cu

clean :
	rm -f WeakStrongCUDA
	rm -f *.o

