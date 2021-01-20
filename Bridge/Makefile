CC=g++
CFLAGS=-I -Wall -pthread -lpigpio -lrt
VERBOSE = TRUE
Bridge: Bridge.o
	$(CC) $(CFLAGS) -o Bridge Bridge.o
	
Bridge.o: Node.hpp Bridge.hpp
	$(CC) $(CFLAGS) -c Bridge.cpp

clean: 
	$(RM) Bridge *.o *~