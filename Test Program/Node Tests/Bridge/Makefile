CC=g++
CFLAGS=-I -Wall -pthread -lpigpio -lrt

bridge: Node.o  bridge.o
	$(CC) $(CFLAGS) -o bridge Node.o Bridge.o
	
bridge.o: Bridge.hpp Node.hpp
	$(CC) $(CFLAGS) -c Bridge.cpp
	
Node.o: Node.hpp

bridge.o: bridge.hpp Node.hpp

clean: 
	$(RM) bridge *.o *~