/*************************************************************************
Bridge.hpp
Bridge node class interface.

The bridge node transfers control and data streams from one connected
Chain of nodes to another. The bridge node does not necessarily do any
processing, it may simple copy data from port inputs to port outputs, but
may look at the destination and sources of the packets to decide which
ports to direct incoming packets to so that they read their destination
more efficiently. 

Author: Dayalan Nair
Date: January 2021
*************************************************************************/


#ifndef BRIDGE_H
#define BRIDGE_H
#include "../Node/Node.hpp"
#include <unistd.h>
class Bridge : public Node
{
protected:
      //Sensor Nodes being Bridged (Daisy chain). stores IDs.
      int sensors[2] = { 0, 0};    
      //max of 2 Sensors in the example
      int numSensors = 0;               
      //only 2 ports as Pi supports 2 SPI channels
      //can be modified to add i2c port
      //may need seperate array for sensor Ports if not using daisy chain
      int ports[2] = { 0, 0};  //1 for sensor, 1 for control
      //ID of control node
      int controlID;

public:
      //Constructor
      Bridge(int id, int cid, int controlPort);// in the example, control port = 0 (main SPI)
      //function for adding sensor to the array of sensors used to verify a users selection
      void addSensor(int sid, int sensorPort);// in the example,  sensor port = 1 (aux SPI)
      //returns a list of sensors connected via daisy chain to the current bridge node
      int* getSensorIDs();
};
#endif
