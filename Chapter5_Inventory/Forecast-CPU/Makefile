CC = g++
CFLAGS = -std=c++17

Forecast : forecast.o Forecast-CPU.o Crash.o importPINS.o importRawData.o parseRow.o regression.o
	$(CC) $(CFLAGS) -o Forecast forecast.o Forecast-CPU.o Crash.o importPINS.o importRawData.o parseRow.o regression.o

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f Forecast
	rm -f *.o
nolog :
	rm -f Forecast-CPU.?17*

