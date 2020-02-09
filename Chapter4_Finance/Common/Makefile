CC = module load gcc/6.2.0 ; g++
CFLAGS = -std=c++17

all : Crash.o createMatrix.o importParameters.o importRawData.o \
	multiplyMatrixVector.o parseRow.o Welford.o

Crash.o : Crash.cpp ReturnValues.h
	$(CC) $(CFLAGS) -c Crash.cpp

createMatrix.o : createMatrix.cpp
	$(CC) $(CFLAGS) -c createMatrix.cpp

importParameters.o : importParameters.cpp Parameters.h ReturnValues.h \
	importRawData.h parseRow.h Crash.h
	$(CC) $(CFLAGS) -c importParameters.cpp

importRawData.o : importRawData.cpp Crash.h Trim.h
	$(CC) $(CFLAGS) -c importRawData.cpp

multiplyMatrixVector.o : multiplyMatrixVector.cpp
	$(CC) $(CFLAGS) -c multiplyMatrixVector.cpp

parseRow.o : parseRow.cpp Trim.h
	$(CC) $(CFLAGS) -c parseRow.cpp

Welford.o : Welford.cpp
	$(CC) $(CFLAGS) -c Welford.cpp

clean :
	rm -f *.o

