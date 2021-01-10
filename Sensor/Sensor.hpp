#ifndef SENSOR_H
#define SENSOR_H
#include "../Node/Node.cpp"

class Sensor : public Node
{
protected:
    char *type;      //Sensor type
    int samplingRate; //sampling rate of the ADC
    int bid;          //id of Bridge to which Sensor belongs

public:
    Sensor(int id, int bridgeID, char *t, int r, int port);
    void setType(char *t);
    char *getType();
    void setSamplingRate(int r);
    int getSamplingRate();
};
#endif