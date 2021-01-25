CC=g++
CFLAGS=-I -Wall -pthread -lpigpio -lrt
VPATH = Node Sensor
DEPS = Node.hpp Sensor.hpp
OBJ = Node.o Sensor.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Sensor: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
	
clean:
	rm -f $(OBJ)/*.o *~ 
