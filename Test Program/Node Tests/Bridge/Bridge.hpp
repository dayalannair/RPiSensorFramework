#ifndef BRIDGE_H
#define BRIDGE_H
#include "Node.cpp"

class Bridge : public Node
{
protected:
      int sensors[2] = { 0, 0};        //Sensor Nodes being Bridged
      //int numSensors = 0;               //max of 2 Sensors
      //first values in input/output ports in control port
      //only 2 ports as Pi supports 2 SPI channels
      //can be modified to add i2c port
      int ports[2] = { 0, 0};  //1 for sensor, 1 for control
      int controlID;

public:
      Bridge(int id, int cid, int controlPort);
      void addSensor(int sid, int sensorPort);
      void displaySensorIDs();
};
#endif
