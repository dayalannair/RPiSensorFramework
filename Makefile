CC=g++
CFLAGS=-I -Wall -pthread -lpigpio -lrt -lwiringPi
VERBOSE = TRUE
VPATH = Node Bridge Control Sensor
DEPS = Node.hpp Data.hpp Control.hpp Sensor.hpp Bridge.hpp Main.hpp 
OBJ = Node.o Data.o Control.o Sensor.o Bridge.o  Main.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
	
clean:
	rm -f $(OBJ)/*.o *~ 