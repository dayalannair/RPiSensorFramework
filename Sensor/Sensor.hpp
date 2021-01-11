/*
Sensor Node class
The constructor does not require a port as a sensor node is only required to connect to 1 sensor.
Here, the sensor data is received through the main SPI port and is sent to the bridge via the auxiliary SPI port.

Author: Dayalan Nair
Date: January 2021
*/

#ifndef SENSOR_H
#define SENSOR_H
#include "../Node/Node.cpp"

class Sensor : public Node
{
protected:
    char *type;      //Sensor type e.g. temperature sensor
    int samplingRate; //sampling rate of the ADC

public:
    Sensor(int id, char *t, int r);
    void setType(char *t);
    char *getType();
    void setSamplingRate(int r);
    int getSamplingRate();
    void executeCommand();
};
#endif