#include "Data.hpp"

int Data::getID()
{
    return sensorID;
}

string Data::toString()
{
    return ("Sensor ID: " + to_string(sensorID) + "\ntime: " + to_string(time) + "\n Value: " + to_string(dataSample));
}
