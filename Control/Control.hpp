#ifndef CONTROL_H
#define CONTROL_H

#include "../Node/Node.cpp"
#include "Data.cpp"

class Control : public Node
{
protected:
  //multiple bridges. Pi can have a max of 2 using SPI
    int bridges[3] = {0, 0, 0}; //Sensor Nodes being Bridged
    int numBridges = 0;           //max of 3 Sensors
    int bridgePorts[3] = {0, 0, 0}; //can combine with bridges i.e. a 2D array
    /*    
      1 = start
      2 = stop
      3 = toggle sampling rate?
      4 = display data
    */
    int bid; //Bridge ID
    BYTE commands[4] = {'1', '2', '3', '4'};
    Data SensorData[]; // array of type Data (see class below). Need DYNAMIC array
    //main user interface through this Node
    //array to hold Sensor data: 2D? account for multiple Sensors and readings

public:
    Control(int controlID);
    void command(BYTE cmd, int sid);
    void addBridge(int bid, int port);
    int getBridges();
    void inputHandler(BYTE cmd);
    void send_c(int bid, BYTE *ctr, unsigned sz);
};
#endif