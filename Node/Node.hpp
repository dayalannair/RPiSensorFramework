/*
Author: Dayalan Nair
Date: January 2021

Node class

This class defines all the neccesary functions and variables that will be used by any type of node in the framework. This includes buffers and functions for receiving
and sending data and commands.

*/
#ifndef NODE_H
#define NODE_H

#include <pigpio.h>
#include <pthread.h>
#include <iostream>
using namespace std;
typedef char BYTE;//spiXfer uses char* not unsigned char
//int nid, int bn,
typedef int SensorDataHandler(BYTE *data, unsigned int sz); 
typedef int NodeControlHandler(int id, BYTE *ctr, unsigned int sz);

class Node
{
protected:
    int nid;
    //allows for selecting a repo node
    bool isRepo = false;
    bool on_off = false;
    //Ports are used as SPI channels in this example. A Raspberry Pi is limited to two ports
    int ports[2] = { 0, 0};  
    //Handles for the two SPI ports
    int spiHandle;
    int spiHandleAux;
    //input and output buffers. The size has been set to (but is not limited to) 8 bytes (chars)
    char tx_buffer[8];
    char rx_buffer[8]; 
    //These are placeholders for handler functions defined in the Main program
    NodeControlHandler * ControlHandlers[256]; // assuming only 16 ports IDs 0..15
    SensorDataHandler *DataHandlers[256];

    BYTE nodeType; 
    //int activeCommand;
    /*
    1 - control
    2 - bridge 
    3 - sensor
    */

public:
    //handlers for receiving commmands and data respectively. Each take in a different handler defined in the Main program
    void recv_c_handler(int port, NodeControlHandler *handler);
    void recv_sd_handler(int port, SensorDataHandler *handler);

    void recv_c(int id);
    void recv_sd(unsigned int sz);

    //send command and data functions. These both make use of spiXfer from the pigpio library
    void send_c(int port, BYTE *ctr, unsigned sz);
    void send_sd(BYTE *data, unsigned sz);

    bool isOn();
    void set_on_off(bool status);

    //this opens the spi channel based on the port (port = spi channel)
    void setupIO(int port);
    int getID();

    //void setActiveCommand(int c);

    //terminates the pigpio gpio
    void closeGPIO();
    //view contents of the rx_buffer. used for debugging
    char* getRxBuffer();
};

#endif