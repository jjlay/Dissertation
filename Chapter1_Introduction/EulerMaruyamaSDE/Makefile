sde : sde.o
	g++ -std=c++17 -o sde sde.o

sde.o : sde.cpp
	g++ -std=c++17 -c sde.cpp

antithetic : antithetic.o
	g++ -std=c++17 -o antithetic antithetic.o

antithetic.o : antithetic.cpp
	g++ -std=c++17 -c antithetic.cpp

clean :
	rm -f *.o
	rm -f antithetic
	rm -f sde

