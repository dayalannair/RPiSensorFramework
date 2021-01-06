#ifndef BRIDGE_H
#define BRIDGE_H
#include "Node.cpp"

class Bridge : public Node
{
private:
      int sensors[2] = [ 0, 0 ];        //Sensor Nodes being Bridged
      int numSensors = 0;               //max of 2 Sensors
      int inputPorts[3] = [ 0, 0, 0 ];  //2 for sensors, 1 for control
      int outputPorts[3] = [ 0, 0, 0 ]; //2 for sensors, 1 for control

public:
      Bridge(int id, int cid, int outPort, int inPort);
      void addSensor(int s, int in, int out);
      void displaySensorIDs();
};
#endif
