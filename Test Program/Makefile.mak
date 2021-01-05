CC=g++
CFLAGS=-I -Wall -pthread -lpigpio -lrt
#DEPS = Node.hpp Data.hpp Sensor.hpp Bridge.hpp Control.hpp
#OBJ = Node.cpp Data.cpp Sensor.cpp Bridge.cpp Control.cpp

Main: Main.o Node.o Data.o Sensor.o Bridge.o Control.o
	$(CC) $(CFLAGS) -o main Main.o Node.o Data.o Sensor.o Bridge.o Control.o
	
Main.o: Main.cpp Node.hpp Data.hpp Sensor.hpp Bridge.hpp Control.hpp
	$(CC) $(CFLAGS) -c main.cpp
	
Node.o: Node.hpp

Data.o: Data.hpp

Sensor.o: Sensor.hpp

Bridge.o: Bridge.hpp

Control.o: Control.hpp