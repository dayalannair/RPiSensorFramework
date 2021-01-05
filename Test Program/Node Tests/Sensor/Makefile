CC=g++
CFLAGS=-I -Wall -pthread -lpigpio -lrt

sensor: Node.o  Sensor.o
	$(CC) $(CFLAGS) -o sensor Node.o Sensor.o
	
sensor.o: Sensor.hpp Node.hpp
	$(CC) $(CFLAGS) -c Sensor.cpp
	
Node.o: Node.hpp

Sensor.o: Sensor.hpp Node.hpp
