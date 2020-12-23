//Implementation of the sensor node class and sensor reading using pigpio

#include <pigpio.h>
#include "Node.cpp"
#include "Sensor.hpp"

Sensor::Sensor(int id, int Bridge, string t, int r, int outPort, int inPort)
{
      isRepo = false;
      nid = id;
      bid = Bridge;
      type = t;
      samplingRate = r;
      outputPort = outPort;
      inputPort = inPort;
}
//get functions will be linked to specific commands sent by the control node
void Sensor::setType(string t)
{
      type = t;
}
string Sensor::getType()
{
      return type;
}
void Sensor::setSamplingRate(int r)
{
      samplingRate = r;
}
string Sensor::getSamplingRate()
{
      return samplingRate;
};

typedef int Sensor::SensorDataHandler(int nid, int bn, byte *data, unsigned sz){
// this is the definition of a function for handing incomming Sensor data (from a sensor or ADC). ontrol command, may need to forward on
// check byte is within range required for being passed on --> call the send_sd
      send_sd(data, sz);
}

// Note: nid = Node ID (destination that the message is for) bn = block number, eg when streaming to make sure pieces are not missing, to connect the pieces


int main()
{
      //dummy data used to set up framework
      int tempSensorData = 4;
      //configure input and output ports

      //convert this node to a sensor node
      Sensor thisNode(456, 789, "temp sensor", 20, 40, 33); //789 is bridge ID
      bool nodeOn = True;
      while (nodeOn)
      {
            //check for received commands
            if (thisNode.isOn == true)
            {
                  //begin sampling
                  //send data from sensor node to output port after formatting
                  //need ADC library
            }
            else
            {
                  //check for command that turns node on
            };
      }
      //terminate pigpio library
      gpioTerminate();
};
