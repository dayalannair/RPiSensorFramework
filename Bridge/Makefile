CC=g++
CFLAGS=-I -Wall -pthread -lpigpio -lrt
VERBOSE = TRUE
Bridge: Bridge.o
	$(CC) $(CFLAGS) -o Bridge Bridge.o
	
Bridge.o: Bridge.hpp
	$(CC) $(CFLAGS) -c Bridge.cpp
	
Bridge.o: Bridge.hpp

clean: 
	$(RM) Bridge *.o *~