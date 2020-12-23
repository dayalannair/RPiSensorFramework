#ifndef NODE_H
#define NODE_H
#include "Node.hpp"

class Sensor : public Node
{
private:
    string type;      //Sensor type
    int samplingRate; //sampling rate of the ADC
    int bid;          //id of Bridge to which Sensor belongs

public:
    Sensor(int id, int Bridge, string t, int r, int outPort, int inPort);
    void setType(string t);
    string getType();
    void setSamplingRate(int r);
    string getSamplingRate();
    typedef int SensorDataHandler(int nid, int bn, byte *data, unsigned sz);
    send_sd(int port, int sid, byte *data, unsigned sz);
};