#include "Data.hpp"

int Data::getID()
{
    return sensorID;
}

string Data::toString()
{
    return ("Sensor ID: " + sensorID + "\ntime: " + time + "\n Value: " + dataSample);
}
