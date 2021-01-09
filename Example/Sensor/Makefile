CC=g++
CFLAGS=-I -Wall -pthread -lpigpio -lrt
VERBOSE = TRUE
Sensor: Sensor.o
	$(CC) $(CFLAGS) -o Sensor Sensor.o
	
Sensor.o: Sensor.hpp
	$(CC) $(CFLAGS) -c Sensor.cpp
	
Sensor.o: Sensor.hpp

clean: 
	$(RM) Sensor *.o *~