CC=g++
CFLAGS=-I -Wall -pthread -lpigpio -lrt
VPATH = Node Control
DEPS = Node.hpp Data.hpp Control.hpp
OBJ = Node.o Data.o Control.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Control: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	
.PHONY: clean
	
clean:
	rm -f $(OBJ)/*.o *~ 