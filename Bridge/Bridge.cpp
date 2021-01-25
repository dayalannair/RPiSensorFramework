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
            cout<<"Sensor with ID: "<<sid<<" added on port: "<<sensorPort<<endl;
        }
        numSensors++;
    }
    else
    {
        cout<<"The maximum number of sensors has been reached."<<endl;
    }
}
int* Bridge::getSensorIDs()
{ //view which Sensor Node is connected to this Bridge
      cout<<"----------------------Display Sensor IDs----------------------------"<<endl;
      for (int i = 0; i < numSensors; i++){
            cout<<"Sensor "<<i+1<<" ID: "<<sensors[0]<<endl;
      }
      return sensors;
}

//================================== Main function ==================================

//Uncomment and add code (such as that seen in the example "Main.cpp") inside the while loop
//Add handlers/copy from the "Main.cpp" program

//=====================================================================================
// int main()
// {
// ------------------ set up node here ----------------------------------------
//       //creates node and sets  port = 0
//       //max id is 256
//       Bridge thisNode(2,1, 0);

//       //add sensors and setup IO
//       thisNode.addSensor(3,1);

// -----------------------------------------------------------------------------
//       
//       //need to change meaning of on - turned on or sensing on
//       thisNode.set_on_off(true);
//       while (thisNode.isOn())
//       {
//           sleep(5);

//           cout<<"Polling now. (5 seconds elapsed)"<<endl;
//           ------------------ add code here ------------------------------




        //--------------------------------------------------------------------
//       }
// }