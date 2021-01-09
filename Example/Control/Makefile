CC=g++
CFLAGS=-I -Wall -pthread -lpigpio -lrt
VERBOSE = TRUE
Control: Control.o
	$(CC) $(CFLAGS) -o Control Control.o
	
Control.o: Control.hpp
	$(CC) $(CFLAGS) -c Control.cpp
	
Control.o: Control.hpp

clean: 
	$(RM) Control *.o *~