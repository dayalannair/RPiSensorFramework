CC=g++
CFLAGS=-I -Wall -pthread -lpigpio -lrt
VERBOSE = TRUE
Control: Control.o
	$(CC) $(CFLAGS) -o Control Control.o
	
Control.o: Node.hpp Control.hpp Control.cpp 
	$(CC) $(CFLAGS) -c Control.cpp

clean: 
	$(RM) Control *.o *~