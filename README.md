# RPiSensorFramework
Framework for a sensor array using Raspberry Pi nodes

### Notes: 

maximum node ID is 256 as it must fit within one byte.

Output/input ports must be in BCM form.

This project uses pigpio


## Example program

The example program will load all three node types as objects on a single Raspberry Pi. Therefore, one needs to comment out the #include "Node.cpp" from the various subclasses to avoid including the Node class three times in a single program. When deployed, each node will require only its specific class and the Node class.

Example program (main.cpp) uses only SPI for communication, and is therefore limited to 2 connections per node as the RPi has 2 only SPI ports.

run the program using sudo ./Main. Sudo required to initialise pigpio daemon.

## Communication packets

### 1. Control packet

The control packet is made up of 4 bytes: 

|      0      |      1      |   2   |     3       |
| ----------- | ----------- | ----- | ------    |
| 'c' - indicates control pkt| id - byte indicating target node ID| cmd - command to be executed|'x' - indicate end of pkt(optional)|


