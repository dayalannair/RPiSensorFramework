# RPiSensorFramework
Framework for a sensor array using Raspberry Pi nodes

Notes: 

maximum node ID is 256 as it must fit within one byte.

Output/input ports must be in BCM form.

This project uses pigpio

## test function programs

These are for testing the communication functions. Once complete, these will be added to the Node class. These require devices for sending/receiving data via SPI e.g. rs232. The selection of the device is left up to the developer.

These methods allow for the user to add/modify a function for converting ADC data into an integer output to be sent out from the sensor node. As an example, a temperature conversion formula will be used, which will convert the adc output of a temperature sensor into a sample in degrees Celsius.

## Example program

The example program will load all three node types as objects on a single Raspberry Pi. Therefore, one needs to comment out the #include "Node.cpp" from the various subclasses to avoid including the Node class three times in a single program. When deployed, each node will require only its specific class and the Node class.

Example program (main.cpp) uses only SPI for communication, and is therefore limited to 2 connections per node as the RPi has 2 only SPI ports.

run the program using sudo ./Main. Sudo required to initialise pigpio daemon.
