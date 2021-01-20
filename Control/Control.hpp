/*
Author: Dayalan Nair
Date: January 2021

Control Node class

This class provides an interface for the user to communicate with the sensors within the framework and to view recorded data.
Attached bridges will be daisy-chained.

*/
#ifndef CONTROL_H
#define CONTROL_H

#include "../Node/Node.hpp"
#include "Data.hpp"

class Control : public Node
{
protected:
  //multiple bridges. Pi can have a max of 2 using SPI

  //IDs of connected bridges
  int bridges[3] = {0, 0, 0}; 
  //number of bridges in the daisy-chain
  int numBridges = 0;           //max of 3 Sensors
  //may not need if using daisy chain
  int bridgePorts[3] = {0, 0, 0}; //can combine with bridges i.e. a 2D array
  /*    
    1 = start
    2 = stop
    3 = toggle sampling rate?
    4 = display data
  */
  //list of valid command that will be recognised by the sensor
  BYTE commands[4] = {'1', '2', '3', '4'};
  Data SensorData[]; // array of type Data (see class below). Need DYNAMIC array
  //main user interface through this Node
  //array to hold Sensor data: 2D? account for multiple Sensors and readings

public:
  //Constructor. only requires an ID (could possibly function without one)
  Control(int controlID);

  //checks if both command and bridgeID is valid before sending packet which includes both the sensor and bridge IDs
  void command(BYTE cmd, int bridgeID, int sensorID);
  
  //adds a bridge to the daisy chain and stores its corresponding ID (could remove port for daisy chain implementation)
  void addBridge(int bid, int port);

  //view all bridges in the daisy chain.
  void displayBridges();

  //allows user to interface with the control node using simple inputs.
  void inputHandler(BYTE cmd);
};
#endif