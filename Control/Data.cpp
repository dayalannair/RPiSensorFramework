#include "Data.hpp"

Data::Data(int ID, int t, BYTE* sample){
    sensorID = ID;
    time = t;
    dataSample = sample;

}

int Data::getID()
{
    return sensorID;
}

//display using cout<<
// string Data::toString()
// {
//     return ("Sensor ID: " + to_string(sensorID) + "\ntime: " + to_string(time) + "\n Value: " + to_string(dataSample));
// }
