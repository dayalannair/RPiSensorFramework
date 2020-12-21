#ifndef CONTROL_H
#define CONTROL_H

#include <iostream>
#include <string>
#include "Node.hpp"
using namespace std;

class Control : public Node
{
private:
    int bridges[3] = [ 0, 0, 0 ]; //Sensor Nodes being Bridged
    int numBridges = 0;           //max of 3 Sensors
    /*    
      1 = start
      2 = stop
      3 = toggle sampling rate?
      4 = display data
    */
    int bid; //Bridge ID
    int commands[4] = {1, 2, 3, 4};
    Data SensorData[]; // array of type Data (see class below)
    //main user interface through this Node
    //array to hold Sensor data: 2D? account for multiple Sensors and readings

public:
    Control(int id, int inPort, int outPort);
    void command(int cmd, int sid);
    int getBridges();
    void inputHandler(int cmd);
};

class Data
{
private:
    int sensorID;
    int time; //may need string
    int dataSample;

public:
    string toString();
};