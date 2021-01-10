//Data object that is stored in an array in the control node.
//The array acts as a repository and would be stored to permanent storage an regular intervals
#ifndef DATA_H
#define DATA_H
#include <string>

class Data
{
private:
    int sensorID;
    int time; //may need string
    int dataSample;

public:
    string toString();
    int getID();
};
#endif