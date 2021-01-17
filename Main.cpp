#include "Main.hpp"
#include <pigpio.h>

// handle an incoming control command, may need to forward on
//not sure how the following 3 functions work together. Ask in next meeting.
int bridge_c_handler(int nid, BYTE *ctr, unsigned int sz)
{
    cout<<"node ID provided: "<<nid<<endl;
    cout<<"control packet: "<<ctr[0]<<" "<<ctr[1]<<" "<<ctr[2]<<endl;
    BYTE type = ctr[0];//indicates that a command is to follow. declare outside fn?
    BYTE command;
    int nodeID;
    nodeID = ctr[1] - '0';//conv to int
    cout<<"Node ID from packet: "<<nodeID<<endl;
//check if node ID of command matches the ID provided. this ID will be 

    if (nodeID == nid){    
        cout<<"Node ID from received packet matches the ID provided"<<endl;
        if (type == 'c'){
            cout<<"Forwarding to sensor node ID: "<<nid<<endl;
            return 2;
        }
        //set the active command which will be executed by sensor
        //cout<<"Node ID from received packet matches the ID provided. Forwarding..."<<endl;
        //setActiveCommand(ctr[2]);
        //return 1;
        //forward command
        return 1;

    }
     
    return 0;
}

int sensor_c_handler(int nid, BYTE *ctr, unsigned int sz){
    BYTE type = ctr[0];//indicates that a command is to follow. declare outside fn?
      BYTE command;
      BYTE nodeID;
      if (type == 'c'){
            if (nodeID == nid){
                  //set the active command which will be executed by sensor
                  cout<<"Node ID from received packet matches the ID provided. Executing..."<<endl;
                  //setActiveCommand(ctr[2]);
                  //execute command
                  //return 1;
            }
      }
      return 0;    


}


int main(){
    char userInput;
    
    

    Sensor sensor(3, 'T', 10); //T = temperature
    
    
    


    cout<<"++++++++++++++++++++++++ Control Node command send/recv test ++++++++++++++++++++++++++++++"<<endl;
    Control control(1);
    control.addBridge(2,0);
    control.displayBridges();

    //turn on sensors with bridge ID 456
    control.command('1', 2, 3);
    char* rx = control.getRxBuffer();

    control.closeGPIO();


    cout<<"++++++++++++++++++++++++ Bridge Node command send/recv test ++++++++++++++++++++++++++++++"<<endl;
    Bridge bridge(2,1,0);
    bridge.addSensor(3,1);
    //turn on sensors with bridge ID 456
    //similar to recv c control bc control wont recv c
    int* bridgeSIDs = bridge.getSensorIDs();
    cout<<bridgeSIDs[0]<<" "<<bridgeSIDs[1]<<endl;
    control.recv_c_handler(0, bridge_c_handler);
    control.recv_c(bridgeSIDs);
    control.closeGPIO();

    //bridge.recv_c(bridgeSIDs);
    //bridge.recv_c_handler(0,)
    //thread for receiving data?
    bool nodeOn = true;
    while (nodeOn)
    {
        cout << "Enter a command \n";
        cout << "1 - start sampling \n";
        cout << "2 - stop sampling \n";
        cout << "3 - change sampling rate \n";
        cout << "4 - view data \n";
        cout << "q - quit \n"; 
        cin >> userInput;
        //pass command to the node's input handler. can add option for exiting program.
        if (userInput == 'q')
        {
            nodeOn = false;
            sensor.closeGPIO();
            bridge.closeGPIO();
            control.closeGPIO();
        }
        else
        {
            control.inputHandler(userInput); //handler must work with input as string
        }
    }

}