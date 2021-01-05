#ifndef CONTROL_H
#define CONTROL_H

#include <iostream>
#include <string>
#include "Node.cpp"
using namespace std;
#include "Data.hpp"

class Control : public Node
{
private:
    int bridges[3] = [ 0, 0, 0 ]; //Sensor Nodes being Bridged
    int numBridges = 0;           //max of 3 Sensors
    int b_outPorts[3] = [0,0,0];
    int b_inPorts[3] = [0,0,0];
    /*    
      1 = start
      2 = stop
      3 = toggle sampling rate?
      4 = display data
    */
    int bid; //Bridge ID
    int commands[4] = {1, 2, 3, 4};
    Data SensorData[]; // array of type Data (see class below). Need DYNAMIC array
    //main user interface through this Node
    //array to hold Sensor data: 2D? account for multiple Sensors and readings

public:
    Control(int id, int inPort, int outPort);
    void command(int cmd, int sid);
    void addBridge(int bid, int in, int out);
    int getBridges();
    void inputHandler(int cmd);
    send_c(int bid, byte *ctr, unsigned sz);
};
