SUBDIRS = Bridge Control Sensor
CC=g++
CFLAGS=-I -Wall -pthread -lpigpio -lrt
VERBOSE = TRUE

Main: Main.o
	$(CC) $(CFLAGS) -o Main Main.o
	
Main.o: Main.hpp
	$(CC) $(CFLAGS) -c Main.cpp
	
Main.o: Main.hpp

all:
	+$(MAKE) -C Bridge
	+$(MAKE) -C Sensor
	+$(MAKE) -C Control

.PHONY: all clean

all clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir -f Makefile $@; \
done
	$(RM) Main *.o *~