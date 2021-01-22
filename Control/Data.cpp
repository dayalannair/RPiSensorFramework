#include "Data.hpp"

Data::Data(int ID, BYTE* t, BYTE* sample, unsigned int sz){
    sensorID = ID;
    time = t;
    for (int i = 0; i<sz;i++){
        dataSample[i] = sample[i]; 

    }

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

void Data::printSample(){

    cout<<"Sensor ID: "<<sensorID<<endl;
    cout<<"Time: "<<time<<endl;
    cout<<"Sample: "<<dataSample<<endl;
}