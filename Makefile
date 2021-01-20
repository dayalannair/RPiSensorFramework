SUBDIRS = Node Bridge Control Sensor
CC=g++
CFLAGS=-I -Wall -pthread -lpigpio -lrt
VERBOSE = TRUE

VPATH = Node Bridge Control Sensor

# Main: Main.o Node.o
# 	$(CC) $(CFLAGS) -o Main Main.o
	

# Main.o: Main.hpp Node.hpp Control.hpp Sensor.hpp Bridge.hpp
# 	$(CC) $(CFLAGS) -c Main.cpp


DEPS = Main.hpp Node.hpp Control.hpp Sensor.hpp Bridge.hpp Data.hpp
OBJ = Main.o Node.o Control.o Sensor.o Bridge.o Data.o

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