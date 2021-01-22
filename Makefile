#SUBDIRS = Node Bridge Control Sensor
CC=g++
CFLAGS=-I -Wall -pthread -lpigpio -lrt
VERBOSE = TRUE

VPATH = Node Bridge Control Sensor

# Main: Main.o Node.o
# 	$(CC) $(CFLAGS) -o Main Main.o
	

# Main.o: Main.hpp Node.hpp Control.hpp Sensor.hpp Bridge.hpp
# 	$(CC) $(CFLAGS) -c Main.cpp


DEPS = Node.hpp Data.hpp Control.hpp Sensor.hpp Bridge.hpp Main.hpp 
OBJ = Node.o Data.o Control.o Sensor.o Bridge.o  Main.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)




#Main.o: Main.hpp
# all:
# 	+$(MAKE) -C Node
# 	+$(MAKE) -C Bridge
# 	+$(MAKE) -C Sensor
# 	+$(MAKE) -C Control

.PHONY: clean
	
clean:
	rm -f $(OBJ)/*.o *~ 

# all clean:
# 	for dir in $(SUBDIRS); do \
# 		$(MAKE) -C $$dir -f Makefile $@; \
# done
# 	$(RM) Main *.o *~