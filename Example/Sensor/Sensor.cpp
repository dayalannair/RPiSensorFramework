//Implementation of the sensor node class and sensor reading using pigpio
#include "Sensor.hpp"

Sensor::Sensor(int id, int bridgeID, char *t, int r, int port)//port can be used to specify control port. using 0 for now
{
      isRepo = false;
      nid = id;
      bid = bridgeID;
      type = t;
      samplingRate = r;

}
//get functions will be linked to specific commands sent by the control node
void Sensor::setType(char *t)
{
      type = t;
}
char *Sensor::getType()
{
      return type;
}
void Sensor::setSamplingRate(int r)
{
      samplingRate = r;
}
int Sensor::getSamplingRate()
{
      return samplingRate;
};

int main()
{
      //dummy data used to set up framework
      int tempSensorData = 4;
      //configure input and output ports

      //convert this node to a sensor node
      Sensor thisNode(456, 789, (BYTE*)"temp",64000, 0); //789 is bridge ID
      thisNode.set_on_off(true);
      while (thisNode.isOn())
      {
            //check for received commands
            if (thisNode.isOn() == true)
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
      gpioTerminate();
};