CC=g++
CFLAGS=-I -Wall -pthread -lpigpio -lrt
VERBOSE = TRUE
NODEDIR= ../Node
INCLUDE = -I.$(NODEDIR)
VPATH=$(NODEDIR)
Node: Node.o
	$(CC) $(CFLAGS) -o Node Node.o

Node.o: Node.hpp Node.cpp
	$(CC) $(CFLAGS) -c Node.cpp

Sensor: Sensor.o
	$(CC) $(CFLAGS) -o Sensor Sensor.o
	
Sensor.o: Sensor.hpp Sensor.cpp Node.hpp
	$(CC) $(CFLAGS) -c Sensor.cpp

clean: 
	$(RM) Sensor Node *.o *~
