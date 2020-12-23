#include "Bridge.hpp"
#include "Node.cpp"
#include <pigpio.h>

Bridge::Bridge(int id, int outPort, int inPort)
{
      isRepo = false;
      nid = id;
      c_outputPort = outPort;
      c_inputPort = inPort;
      nodeType = 2;
      //set up control gpio
      setupIO(outPort, inPort);

}
void Bridge::addSensor(int s, int outPort, int inPort)
{ //connect a Sensor Node to the Bridge Node
      if (numSensors < 3)
      {
            //add sensor ID and ports to memory (array)
            sensors[numSensors] = s;
            inputPorts[numSensors] = inPort;
            outputSensors[numSensors] = outPort;
            //set up IO for sensor node
            setupIO(outPort, inPort);
            numSensors++;
      }
      else
      {
            printf("The maximum number of sensors for this bridge has been reached.")
      }
}
void Bridge::displaySensorIDs()
{ //view which Sensor Node is connected to this Bridge
      cout << "Sensor IDs connected to bridge " + nid;
      for (int i = 0; i < numSensors; i++)
      {
            cout << sensors[i] + "\n"
      }
}

recv_sd_handler(port, DataHandler* handler){

      
}        // tell system what function to call on incoming sensor data (packets or bytes)

int main()
{
      //creates node and sets control input and output ports
      //max id is 256
      Bridge thisNode(189, 16, 26);

      //add sensors and setup IO
      thisNode.addSensor(234,12,14);
      thisNode.addSensor(214,15,18);

      bool nodeOn = True;
      while (nodeOn)
      {
            //check for received commands
            if (thisNode.isOn == true)
            {
                  //receive data from sensor/s
                  //forward as packets incl. time, sensor ID and data
                  //use SPI
            }
            else
            {
                  pass;
            };
      }