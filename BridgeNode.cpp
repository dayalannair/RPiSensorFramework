#include "BridgeNode.hpp"
#include "Node.cpp"

Bridge::Bridge(int id, int cid, int outPort, int inPort)
{
      isRepo = false;
      nid = id;
      controlId = cid;
      outputPort = outPort;
      inputPort = inPort;
}
void Bridge::addSensor(int s)
{ //connect a Sensor Node to the Bridge Node
      if (numSensors < 3)
      {
            sensors[numSensors] = s;
            numSensors++;
      }
      else
      {
            printf("The maximum number of sensors for this bridge has been reached.")
      }
}
string Bridge::getSid()
{ //view which Sensor Node is connected to this Bridge
      return sid;
}

int main()
{
      Bridge thisNode(789, 234, 40, 33);
      bool nodeOn = True;
      while (nodeOn)
      {
            //check for received commands
            if (thisNode.isOn == true)
            {
                  //receive data from sensor/s
                  //forward as packets incl. time, sensor ID and data
            }
            else
            {
                  pass;
            };
      }