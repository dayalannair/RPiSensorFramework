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
      ports[1] = sensorPort;
      setupIO(sensorPort);
      //one sensor for RPi SPI
      sensors[0] = sid;

//code below for multiple sensors
      // if (numSensors < 3)
      // {
      //       //add sensor ID and ports to memory (array)
      //       sensors[numSensors] = s;
      //       inputPorts[numSensors] = inPort;
      //       outputSensors[numSensors] = outPort;
      //       //set up IO for sensor node
      //       setupIO(outPort, inPort);
      //       numSensors++;
      // }
      // else
      // {
      //       cout<<"The maximum number of sensors for this bridge has been reached.";
      // }
}
void Bridge::displaySensorIDs()
{ //view which Sensor Node is connected to this Bridge
      cout<<sensors[0];
      
      //multiple sensors
      // cout << "Sensor IDs connected to bridge " + nid;
      // for (int i = 0; i < numSensors; i++)
      // {
      //       cout << sensors[i] + "\n";
      // }
}


int main()
{
      //creates node and sets control input and output ports
      //max id is 256
      Bridge thisNode(189,345, 0);

      //add sensors and setup IO
      thisNode.addSensor(234,1);
      //thisNode.addSensor(214,15,18);
      //need to change meaning of on - turned on or sensing on
      thisNode.set_on_off(true);
      while (thisNode.isOn())
      {
            //check for received commands
            if (thisNode.isOn() == true)
            {
                  //receive data from sensor/s
                  //forward as packets incl. time, sensor ID and data
                  //use SPI
            }
            else
            {
                  
            };
      }
}