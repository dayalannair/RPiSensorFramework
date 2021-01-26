/**********************************************************************************
Sensor.hpp
Sensor Node class

This is a Node subclass which is designed to interface directly with the sensor 
and can execute commands received from the bridge node.
These nodes can be daisy-chained: data will flow towards the bridge and commands 
will be excuted by nodes with IDs matching that which was received with the command.

Author: Dayalan Nair
Date: January 2021
***********************************************************************************/

#ifndef SENSOR_H
#define SENSOR_H
#include "../Node/Node.hpp"

class Sensor : public Node
{
protected:
    //Sensor type e.g. temperature sensor
    char type;      
    //sampling rate of the ADC
    int samplingRate; 

public:
    //Contructor. This sets the node's ID as well as an initial sampling rate and sensor type
    Sensor(int id, char t, int r);
    //-------------------------------set functions--------------------------------
    void setType(char t);
    void setSamplingRate(int r);
    //-------------------------------get functions--------------------------------
    char getType();
    int getSamplingRate();
    //function to execute commands. the command BYTE is passed to the function after being extracted from the control packet by a handler
    void executeCommand(BYTE cmd);
    //on function would be used to initiate threading if required
    void on();
    
};
#endif