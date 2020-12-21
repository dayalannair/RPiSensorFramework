#ifndef BRIDGE_H
#define BRIDGE_H
#include "Node.hpp"

class Bridge : public Node
{
private:
      int sensors[3] = [ 0, 0, 0 ]; //Sensor Nodes being Bridged
      int numSensors = 0;           //max of 3 Sensors
      int controlId = 0;

public:
      Bridge(int id, int cid, int outPort, int inPort);
      void addSensor(int s);
      string getSid();
};
