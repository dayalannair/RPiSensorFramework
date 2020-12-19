/* 
RPiSensor Streaming Framework 
Created by: Dayalan Nair 
Date: December 2020
*/

class Node {
public:
      //constructor. Is it necessary as there is no need for a general node?
      Node(int id){ 
            nid = id;
      }

      // handle an incoming control command, may need to forward on
      typedef int NodeControlHandler (int nid, byte ctr, unsigned sz);   

      //switch statement for node to decide on what operation to perform based on a given command
      switch(ctr){
            //start sensing 
            case 1: 
            //if Node NOT a Sensor Node (use different id formats i.e. SN1234 vs. BN1234),
            //forward.
            //determine port from the id
            send_c(port, bn, ctr);
            //if Node is a Sensor Node, start sampling.

            //stop sensing
            case 2:
            //same concept as above

            //change sampling rate
            case 3:


      }

      recv_sd_handler(int port, int data, DataHandler* handler);       
      // tell system what function to call on incoming Sensor data (packets or bytes)
      if (nid[0] == 'S') OR (nid[0] == 'B'){ //if Node is Sensor or Bridge, forward
            forward_data(port, data);
            } 
      else{
            //write data to repository. may not need else statement as the control Node can write data directly from port to repo
      }

      //send to control/repo Node

      send_c(int port, int bn, byte* ctr, unsigned sz);      // send control out a port
      forward_data(int port, int data, unsigned sz);      // send data out a port

      
      recv_c_handler(int port, NodeControlHandler){
            //links port to the handler?


      };      // indicate function to handle an incoming configuration command
      
      
      // optional if needed… the develop might just decide to use fwrite or implement the way to talk to a particular port directly in the send_sd function
      outp (int port, byte data);     // this would just be a wrapper function, would send a data item out a port,  like putc 


      outpd (int port, byte* data, unsigned sz);     // this would just be a wrapper function, would send a data item out a port like fwrite

private: //use protected for inheritance
      int nid; //Node ID
      //add additional Node variables and functions
};
//Sensor Node
class Sensor: public Node { 

private:
      string type; //Sensor type
      int samplingRate; //sampling rate of the ADC
      int bid; //id of Bridge to which Sensor belongs

public:
      Sensor(int id, int Bridge, string t, int r){
            nid = id;
            bid = Bridge;
            type = t;
            samplingRate = r;
      }
      void setType(string t){
            type = t;
      }
      string getType(){
            return type;
      }
      void setSamplingRate(int r){
            samplingRate = r;
      }
      string getSamplingRate(){
            return samplingRate;
      };

      typedef int SensorDataHandler (int nid, int bn, byte* data, unsigned sz); 
      // this is the definition of a function for handing incomming Sensor data. ontrol command, may need to forward on
		// check byte is within range required for being passed on --> call the send_sd
		// pass data on to the Bridge Node
     // Note: nid = Node ID (destination that the message is for) bn = block number, eg when streaming to make sure pieces are not missing, to connect the pieces

     send_sd(int port, int sid, byte* data, unsigned sz);  
      // send Sensor data (i.e. _sd in the function name indicates this) out a port.  sid = Sensor ID, e.g. temp senor 1
      // send to the Sensor with the corresponding id




};
//Bridge Node
class Bridge: public Node {
 private:
      int sensors[3] = [0,0,0]; //Sensor Nodes being Bridged
      int numSensors = 0; //max of 3 Sensors
      int controlId = 0;

public:
      Bridge(int id, int cid){
            nid = id;
            controlId = cid;
      };
       void addSensor(int s){ //connect a Sensor Node to the Bridge Node
            if (numSensors < 3){
                  sensors[numSensors] = s;
                  numSensors++;
            }
            else{
                  printf("The maximum number of sensors for this bridge has been reached.")
            }
            
      };
      string getSid(){ //view which Sensor Node is connected to this Bridge
            return sid;
      };
};
//Control Node
class control: public Node { 
private:
      int bridges[3] = [0,0,0]; //Sensor Nodes being Bridged
      int numBridges = 0; //max of 3 Sensors

      /*    
      1 = start
      2 = stop
      3 = toggle sampling rate?
      */
      int bid; //Bridge ID
      int commands[3] = {1, 2, 3}
      int SensorData[];
      //main user interface through this Node
      //array to hold Sensor data: 2D? account for multiple Sensors and readings

public:
      control(int id){ //constructor
            nid = id;
      }
      //commands affect all Nodes or one in particular?
      void command(int cmd, int sid){
            // send out command to all Bridges which in turn send out to all Sensors

      }

      /*
      function for connecting a bridge to the control node. this function can be made into a general addNode() function,
      which could be part of the Node class and allow for adding both sensors to bridges and bridges to control nodes
      (same structure as addSensor() in the Bridge class).

      */
      void addBridge(int b){ //connect a Sensor Node to the Bridge Node
            if (numBridges < 3){
                  bridges[numBridges] = b;
                  numBridges++;
            }
            else{
                  printf("The maximum number of bridges has been reached.")
            }
            
      };

      int getBridges(){};


};

int main(){
      //these could be made higher level i.e. allow user to enter these details/set up nodes via command line

      //create control Node with id 123 - choose integers to reduce data transmission size
      control C1(123);

      //create Bridge B1 and link to control node
      Bridge B1(321, 123);
      
      //add bridge to control node
      C1.addBridge(321)

      //create two Sensors 
      Sensor S1(456);
      Sensor S2(567);

      //add sensors to the bridge B1
      B1.addSensor(456);
      B1.addSensor(567);





};












