CC=g++
CFLAGS=-I -Wall -pthread -lpigpio -lrt
VERBOSE = TRUE
Bridge: Node.o  Bridge.o
	$(CC) $(CFLAGS) -o Bridge Node.o Bridge.o
	
Bridge.o: Bridge.hpp Node.hpp
	$(CC) $(CFLAGS) -c Bridge.cpp
	
Node.o: Node.hpp

Bridge.o: Bridge.hpp Node.hpp

clean: 
	$(RM) Bridge *.o *~