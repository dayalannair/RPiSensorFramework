/*
Author: Dayalan Nair
Date: January 2021

Data class

A simple object for storing information on a particular sample. Stored in an array in the control node.
The array acts as a repository and would be transferred to permanent storage at regular intervals.
*/
#ifndef DATA_H
#define DATA_H
#include <string>

class Data
{
private:
    //ID of sensor from which data was received
    int sensorID;
    //time at which sample was received by the control node
    int time; //may need string
    //the data (possibly formatted) corresponding to the sample.
    int dataSample;

public:
    //displays a particular sample
    string toString();
    //returns the ID of the sensor that recorded the sample.
    int getID();
};
#endif