# RPiSensorFramework
Framework for a sensor array using Raspberry Pi nodes

Notes: 

maximum node ID is 256 as it must fit within one byte.

Output/input ports must be in BCM form.

This project uses pigpio

## test function programs

These are for testing the communication functions. Once complete, these will be added to the Node class. These require devices for sending/receiving data via SPI e.g. rs232. The selection of the device is left up to the developer.

These methods allow for the user to add/modify a function for converting ADC data into an integer output to be sent out from the sensor node. As an example, a temperature conversion formula will be used, which will convert the adc output of a temperature sensor into a sample in degrees Celsius.
