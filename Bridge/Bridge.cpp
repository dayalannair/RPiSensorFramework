#include "Bridge.hpp"

Bridge::Bridge(int id, int cid, int controlPort)
{
      isRepo = false;
      nid = id;
      nodeType = 2;
      controlID = cid;
      //set up control spi
      setupIO(controlPort);

}
void Bridge::addSensor(int sid, int sensorPort)
{ //connect a Sensor Node to the Bridge Node
if (numSensors < 3)
    {
        //add sensor ID and ports to memory (array)
        sensors[numSensors] = sid;
        ports[numSensors] = sensorPort;
        //set up IO for sensor node
        //port must = 0 OR 1 for RPi and a max of 2 bridges.
        if (sensorPort < 2 && sensorPort>=0){
            setupIO(sensorPort);
            cout<<"Sensor with ID: "<<sid<<"added on port: "<<sensorPort<<endl;
        }
        numSensors++;
    }
    else
    {
        cout<<"The maximum number of sensors has been reached."<<endl;
    }
}
void Bridge::displaySensorIDs()
{ //view which Sensor Node is connected to this Bridge
      cout<<"----------------------Display Sensor IDs----------------------------"<<endl;
      for (int i = 0; i < numSensors; i++){
            cout<<"Sensor "<<i+1<<" ID: "<<sensors[0]<<endl;
      }
}


// int main()
// {
//       //creates node and sets control input and output ports
//       //max id is 256
//       Bridge thisNode(189,345, 0);

//       //add sensors and setup IO
//       thisNode.addSensor(234,1);
//       //thisNode.addSensor(214,15,18);
//       //need to change meaning of on - turned on or sensing on
//       thisNode.set_on_off(true);
//       while (thisNode.isOn())
//       {
//             //check for received commands
//             if (thisNode.isOn() == true)
//             {
//                   //receive data from sensor/s
//                   //forward as packets incl. time, sensor ID and data
//                   //use SPI
//             }
//             else
//             {
                  
//             };
//       }
// }