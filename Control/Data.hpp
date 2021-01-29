/*
Author: Dayalan Nair
Date: January 2021

Data class

A simple object for storing information on a particular sample. Stored in an array in the control node.
The array acts as a repository and would be transferred to permanent storage at regular intervals.  

*/
#ifndef DATA_H
#define DATA_H
#include <iostream>
//string library required for toString method
#include <string>
#include <ctime>
using namespace std;
typedef char BYTE;

class Data
{
protected:
    //ID of sensor from which data was received
    int sensorID;
    //time at which sample was received by the control node
    BYTE* time; //may need string
    //the data (possibly formatted) corresponding to the sample.
    BYTE dataSample[64];
    //size of sample stored in data array
    int size;

public:
    //Contructor
    Data(int ID, BYTE* t, BYTE* sample, unsigned int sz);
    //returns the ID of the sensor that recorded the sample.
    int getID();
    //displays a particular sample
    void printSample();
};
#endif
