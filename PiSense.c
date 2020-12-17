
class node {
public:
      node(int id){ //constructor
            nid = id;
      }
      //get and set required? unlikely

      typedef int NodeControlHandler (int nid, byte ctr, unsigned sz);   // handle an incoming control command, may need to forward on

      switch(ctr){
            //start sensing 
            case 1: 
            //if node NOT a sensor node (use different id formats i.e. SN1234 vs. BN1234),
            //forward.
            //determine port from the id
            send_c(port, bn, ctr);
            //if node is a sensor node, start sampling.

            //stop sensing
            case 2:
            //same concept as above

            //change sampling rate
            case 3:


      }

      recv_sd_handler(int port, int data, DataHandler* handler);       
      // tell system what function to call on incoming sensor data (packets or bytes)
      if (nid[0] == 'S') OR (nid[0] == 'B'){ //if node is sensor or bridge, forward
            forward_data(port, data);
            } 
      else{
            //write data to repository. may not need else statement as the control node can write data directly from port to repo
      }

      //send to control/repo node

      send_c(int port, int bn, byte* ctr, unsigned sz);      // send control out a port
      forward_data(int port, int data, unsigned sz);      // send data out a port

      
      recv_c_handler(int port, NodeControlHandler){
            //links port to the handler?


      };      // indicate function to handle an incoming configuration command
      
      
      // optional if needed… the develop might just decide to use fwrite or implement the way to talk to a particular port directly in the send_sd function
      outp (int port, byte data);     // this would just be a wrapper function, would send a data item out a port,  like putc 


      outpd (int port, byte* data, unsigned sz);     // this would just be a wrapper function, would send a data item out a port like fwrite

private: //use protected for inheritance
      int nid; //node ID
      //add additional node variables and functions
};
//Sensor node
class sensor: public node { 

private:
      string type; //sensor type
      int samplingRate; //sampling rate of the ADC
      int bid; //id of bridge to which sensor belongs

public:
      sensor(int id, int bridge, string t, int r){
            nid = id;
            bid = bridge;
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
      }

      typedef int SensorDataHandler (int nid, int bn, byte* data, unsigned sz); 
      // this is the definition of a function for handing incomming sensor data. ontrol command, may need to forward on
		// check byte is within range required for being passed on --> call the send_sd
		// pass data on to the bridge node
     // Note: nid = node ID (destination that the message is for) bn = block number, eg when streaming to make sure pieces are not missing, to connect the pieces

     send_sd(int port, int sid, byte* data, unsigned sz);  
      // send sensor data (i.e. _sd in the function name indicates this) out a port.  sid = sensor ID, e.g. temp senor 1
      // send to the sensor with the corresponding id




};
//Bridge node
class bridge: public node {
 private:
      int sid; //id of the sensor node being bridged
      //need to code for multiple sensors

public:
      bridge(int id, int sensor){
            nid = id;
            sid = sensor;
            
      } 
       void setSid(int s){ //connect a sensor node to the bridge node
            sid = s;
      }
      string getSid(){ //view which sensor node is connected to this bridge
            return sid;
      }




};
//Control node
class control: public node { 
public:
      //commands affect all nodes or one in particular?
      void command(int cmd, int sid){
            // send out command to all bridges which in turn send out to all sensors

      }

private:

/*
1 = start
2 = stop
3 = toggle sampling rate?
*/
int bid; //bridge ID
int commands[3] = {1, 2, 3}
int sensorData[];
//main user interface through this node
//array to hold sensor data: 2D? account for multiple sensors and readings

};












