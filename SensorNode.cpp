

//Sensor Node
class Sensor : public Node
{

private:
      string type;      //Sensor type
      int samplingRate; //sampling rate of the ADC
      int bid;          //id of Bridge to which Sensor belongs

public:
      Sensor(int id, int Bridge, string t, int r, int outPort, int inPort)
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
      void setType(string t)
      {
            type = t;
      }
      string getType()
      {
            return type;
      }
      void setSamplingRate(int r)
      {
            samplingRate = r;
      }
      string getSamplingRate()
      {
            return samplingRate;
      };

      typedef int SensorDataHandler(int nid, int bn, byte *data, unsigned sz);
      // this is the definition of a function for handing incomming Sensor data (from a sensor or ADC). ontrol command, may need to forward on
      // check byte is within range required for being passed on --> call the send_sd
      // pass data on to the Bridge Node
      // Note: nid = Node ID (destination that the message is for) bn = block number, eg when streaming to make sure pieces are not missing, to connect the pieces

      send_sd(int port, int sid, byte *data, unsigned sz);
      // send Sensor data (i.e. _sd in the function name indicates this) out a port.  sid = Sensor ID, e.g. temp senor 1
      // send to the Sensor with the corresponding id
};

 int main()
{
    //dummy data used to set up framework
    int tempSensorData = 4;
    //configure input and output ports

    //convert this node to a sensor node
    Sensor thisNode(456, 789, "temp sensor", 20, 40, 33); //789 is bridge ID
    bool nodeOn = True;
    while (nodeOn){
        //check for received commands
        if (thisNode.isOn == true){
            //begin sampling
            //send data from sensor node to output port after formatting
            //need ADC library 



        }
        else 
        {
            pass;
        };




    }



};
