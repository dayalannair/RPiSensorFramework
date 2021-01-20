#ifndef BRIDGE_H
#define BRIDGE_H
#include "../Node/Node.hpp"

class Bridge : public Node
{
protected:
      int sensors[2] = { 0, 0};        //Sensor Nodes being Bridged. stores IDs.
      int numSensors = 0;               //max of 2 Sensors
      //first values in input/output ports in control port
      //only 2 ports as Pi supports 2 SPI channels
      //can be modified to add i2c port
      //may need seperate array for sensor Ports if >1 sensor
      int ports[2] = { 0, 0};  //1 for sensor, 1 for control
      int controlID;

public:
      Bridge(int id, int cid, int controlPort);// control port = 0 (main SPI)
      void addSensor(int sid, int sensorPort);// sensor port = 1 (aux SPI)
      int* getSensorIDs();
};
#endif
