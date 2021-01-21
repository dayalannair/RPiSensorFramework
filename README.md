# RPiSensorFramework
Application framework for a sensor array using Raspberry Pi nodes. This is to be used as a changeable/adaptable baseline, with the intention of developers modifying it as needed.

### Notes: 

maximum node ID is 256 as it must fit within one byte.

Output/input ports must be in BCM form.

This project uses pigpio

## Example program

The example program will load all three node types as objects on a single Raspberry Pi. Therefore, one needs to comment out the #include "Node.cpp" from the various subclasses to avoid including the Node class three times in a single program. When deployed, each node will require only its specific class and the Node class.

Example program (main.cpp) uses only SPI for communication, and is therefore limited to 2 connections per node as the RPi has 2 only SPI ports.

run the program using sudo ./Main. Sudo required to initialise pigpio daemon.

The Raspberry Pi will have to be connected in spi loopback mode i.e. connect the MOSI pin to the MISO. 

### Handlers

#### Bridge control handler

This handler checks that the target node belongs to the bridge, which reduces flooding in the network, before forwarding to the target node.

#### Sensor control handler

This checks that the node is the target node, and then executes the command.

#### Bridge data handler

Forwards data to control node.

#### Control data handler

Unpacks data and stores in a repository, using Data objects. (see Data class in Control folder).

## Communication packets

Received packets are read from the rx_buffer, which is refreshed whenever sent out of the node via spi (spiXfer).

### 1. Control packet

#### 1.1 Bridge control packet

The control packet received by the bridge node from the control node is made up of 4 bytes: 

|      0      |      1      |   2   |     3       |
| ----------- | ----------- | ----- | ------    |
| 'c' - indicates control pkt| sensor ID - byte indicating target node ID|bridge ID - byte indicating target bridge ID |cmd - command to be executed|

#### 1.2 Sensor control packet

The control packet received by the sensor node from the bridge node is made up of 3 bytes: 

|      0      |      1      |   2   |
| ----------- | ----------- | ----- |
| 'c' - indicates control pkt| sensor ID - byte indicating target node ID|cmd - command to be executed|

### 2. Data packet

The data packet is made up as follows:

|      0      |      1      |       2      |  3 -> 2+sz  |
| ----------- | ----------- | ----- |----- |
| 'd' - indicates data pkt| sensor ID - ID of sensor that recorded data |sz - size of data in packet| data|

If a 'd' is found in the data (e.g. the ASCII integer), the next byte will be analysed. If this byte is not in the range of a typical sz byte, the data will continue to be read as normal. Otherwise, the device will read in the next byte as the sz (size) of data to follow.

An end-of-packet indicator may not be neccesary as the sz bit could be used for this purpose.

No target ID is needed, as the only target for a data packet (denoted by 'd') is the control node.


