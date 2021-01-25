CC=g++
CFLAGS=-I -Wall -pthread -lpigpio -lrt
VPATH = ../Node Bridge
DEPS = Node.hpp Bridge.hpp
OBJ = Node.o Bridge.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Bridge: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
	
clean:
	rm -f $(OBJ)/*.o *~ 