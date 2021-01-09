SUBDIRS = Bridge Control Sensor
all:
	+$(MAKE) -C Bridge
	+$(MAKE) -C Sensor
	+$(MAKE) -C Control

.PHONY: all clean

all clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir -f Makefile $@; \
done