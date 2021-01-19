/*





*/
#include "Main.hpp"
#include <pigpio.h>


//Global variables to facilitate example on a single device
Control control(1);
Bridge bridge(2,1,0);
Sensor sensor(3, 'T', 10); //T = temperature

int bridge_c_handler(int nid, BYTE *ctr, unsigned int sz)
{
    cout<<"node ID provided: "<<nid<<endl;
    cout<<"control packet: "<<ctr[0]<<" "<<ctr[1]<<" "<<ctr[2]<<endl;
    BYTE type = ctr[0];//indicates that a command is to follow. declare outside fn?
    BYTE command;
    int nodeID = ctr[1] - '0';//conv to int;
    cout<<"Node ID from packet: "<<nodeID<<endl;
//check if node ID of command matches the ID provided. this ID will be 

    if (nodeID == nid){    
        cout<<"Node ID from received packet matches the ID provided"<<endl;
        if (type == 'c'){
            cout<<"Forwarding to sensor node ID: "<<nid<<endl;
            //port 1 is output to sensor/daisy chain
            bridge.send_c(1,ctr, 3);
            return 2;
        }
        return 1;

    }
     
    return 0;
}

int sensor_c_handler(int nid, BYTE *ctr, unsigned int sz){
    cout<<"control packet: "<<ctr[0]<<" "<<ctr[1]<<" "<<ctr[2]<<endl;
    cout<<"provided ID: "<<nid<<endl;
    BYTE type = ctr[0];//indicates that a command is to follow. declare outside fn?
      BYTE command;
      int nodeID = ctr[1] - '0';//conv to int;
      if (type == 'c'){
            if (nodeID == nid){
                //set the active command which will be executed by sensor
                cout<<"Node ID from received packet matches the ID provided. Executing..."<<endl;
                cout<<"Command: "<<ctr[2]<<endl;
                sensor.executeCommand(ctr[2]);
                //execute command
                return 3;
            }
      }
      return 0;    


}

int bridge_d_handler(int nid, BYTE *ctr, unsigned int sz)
{
    
    //cout<<"data packet: "<<ctr[0]<<" "<<ctr[1]<<" "<<ctr[2]<<endl;
    BYTE type = ctr[0];//indicates that a command is to follow. declare outside fn?
    BYTE command;
    
    
    int nodeID = ctr[1] - '0';//conv to int;
    cout<<"Node ID from packet: "<<nodeID<<endl;
//check if node ID of command matches the ID provided. this ID will be 

    if (nodeID == nid){    
        cout<<"Node ID from received packet matches the ID provided"<<endl;
        if (type == 'c'){
            cout<<"Forwarding to sensor node ID: "<<nid<<endl;
            //port 1 is output to sensor/daisy chain
            bridge.send_c(1,ctr, 3);
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


int main(){
    char userInput;
    
    control.addBridge(2,0);
    bridge.addSensor(3,1);
    cout<<"++++++++++++++++++++++++ Control & Bridge Node command send/recv test ++++++++++++++++++++++++++++++"<<endl;
    control.displayBridges();

    //turn on sensors with bridge ID 456
    control.command('1', 2, 3);
    char* rx = control.getRxBuffer();
    control.recv_c_handler(0, bridge_c_handler);

    int* bridgeSIDs = bridge.getSensorIDs();
    control.recv_c(bridgeSIDs);
    //control.closeGPIO();


    //cout<<"++++++++++++++++++++++++ Bridge Node command send/recv test ++++++++++++++++++++++++++++++"<<endl;
    

cout<<endl<<"++++++++++++++++++++++++ Sensor Node command send/recv test ++++++++++++++++++++++++++++++"<<endl<<endl;
    //thread for receiving data?

    //simulate incoming command
    BYTE to_send[3];
    //-----------------control packet--------------------
    to_send[0] = 'c';
    to_send[1] = sensor.getID() + '0';
    //cout<<"sensor id: "<<sensorID<<endl;
    to_send[2] = '1';//cmd = 1
    //---------------------------------------------------
    //BYTE *ptr = to_send;

    cout<< "Sent by bridge to sensor: "<<(BYTE*)to_send<<endl;

    sensor.send_c(0, (BYTE*)to_send, 3); 

    sensor.recv_c_handler(0, sensor_c_handler);
    sensor.recv_c(bridgeSIDs);//bridge sids for now
    //sensor.setActiveCommand(command);
    //cout<<"Active command: " << sensor.getActiveCommand()<<endl;
    cout<<"---------------------Next command---------------------------"<<endl;
    to_send[2] = '3';//cmd = 1
    sensor.send_c(0, (BYTE*)to_send, 3); //send cmd to sensor using loop back
    sensor.recv_c(bridgeSIDs);


    sensor.closeGPIO();
    cout<<endl<<"---------------------User interface-------------------------"<<endl<<endl;
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