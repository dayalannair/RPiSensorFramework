/*





*/
#include "Main.hpp"
#include <pigpio.h>


//Global variables to facilitate example on a single device
Control control(1);
Bridge bridge(2,1,0);
Sensor sensor(3, 'T', 10); //T = temperature

int bridge_c_handler(int nid, BYTE *ctr, unsigned int sz)//may not need sz here since pckt is fixed size
{
    cout<<"Current node ID: "<<nid<<endl;
    cout<<"control packet: "<<ctr[0]<<" "<<ctr[1]<<" "<<ctr[2]<<" "<<ctr[3]<<endl;
    BYTE type = ctr[0];
    int sensorID = ctr[1] - '0';//conv to int;
    int bridgeID = ctr[2] - '0';
    cout<<"Node ID from packet: "<<bridgeID<<endl;
//check if node ID of command matches the ID provided. this ID will be 

    if (bridgeID == nid){    
        cout<<"Node ID from received packet matches the bridge ID"<<endl;
        if (type == 'c'){
            cout<<"Forwarding to sensor node ID: "<<nid<<endl;
            BYTE to_send[3];
            //-----------------control packet--------------------
            to_send[0] = 'c';
            to_send[1] = sensorID + '0';
            to_send[2] = ctr[3];
            //port 1 is output to sensor/daisy chain
            bridge.send_c(1,(BYTE*)to_send, 3);
            return 2;
        }
    }
    else{

        cout<<"Forwarding to next bridge..."<<endl;
    }
        return 1;
     
    return 0;
}

int sensor_c_handler(int nid, BYTE *ctr, unsigned int sz){
    cout<<"control packet: "<<ctr[0]<<" "<<ctr[1]<<" "<<ctr[2]<<" "<<ctr[3]<<endl;
    cout<<"Current node ID: "<<nid<<endl;
    BYTE type = ctr[0];
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
/*
=====================================================================================
Handler for a bridge receiving data from a sensor
=====================================================================================

*/
int bridge_d_handler(BYTE *ctr, unsigned int sz)
{
    
    //cout<<"data packet: "<<ctr[0]<<" "<<ctr[1]<<" "<<ctr[2]<<endl;
    BYTE type = ctr[0];
    int size = ctr[2]-'0';
    cout<<"Sensor ID of node that recorded data: "<<ctr[1]<<endl;
    cout<<"size of data (from packet): "<<size<<endl<<"Received data: ";
    
    for (int i = 0; i < size;i++){
        cout<<ctr[i+3];
    }
    cout<<endl;
    if (type == 'd'){
            cout<<"Forwarding data to control node "<<endl;
            //port 1 is output to sensor/daisy chain
            bridge.send_c(0,ctr, sz);
            return 2;
        }
    else{
        cout<<"Data handler called on non-data packet."<<endl;
        return 1;
    }

    return 0;
}

/*
=====================================================================================
Handler for a control node receiving data from a bridge
=====================================================================================

*/
int control_d_handler(BYTE *data, unsigned int sz)
{
    
    //cout<<"data packet: "<<ctr[0]<<" "<<ctr[1]<<" "<<ctr[2]<<endl;
    BYTE type = data[0];
    int sensorID = data[1] - '0';
    int size = data[2]-'0';
    BYTE extracted_data[sz-3];
    cout<<"Sensor ID of node that recorded data: "<<sensorID<<endl;
    
    
    
    
    if (type == 'd'){
        cout<<"size of data (from packet): "<<size<<endl<<"Received data: ";
        for (int i = 0; i < size;i++){
            cout<<data[i+3];
            extracted_data[i] = data[i+3];

        }
        cout<<endl;
        time_t now = time(0);
        char* dt = ctime(&now);
        cout<<"Storing... "<<endl;
        control.saveData(sensorID,dt,extracted_data,sz-3);

        return 2;
        }
    else{
        cout<<"Data handler called on non-data packet."<<endl;
        return 1;
    }

    return 0;
}


int main(){
    char userInput;
    control.addBridge(2,0);
    bridge.addSensor(3,1);
    cout<<"================= Control Node command send/recv test ======================="<<endl;
    control.displayBridges();

    //turn on sensors with bridge ID 456
    control.command('1', 2, 3);
    //char* rx = control.getRxBuffer();
    control.recv_c_handler(0, bridge_c_handler);

    //int* bridgeSIDs = bridge.getSensorIDs();  used if not using daisy chain
    control.recv_c(control.getID());
    //control.closeGPIO();


    cout<<"================= Bridge Node command send/recv test ======================="<<endl;
    //simulate incoming command
    BYTE to_send[4];
    //-----------------control packet--------------------
    to_send[0] = 'c';
    to_send[1] = sensor.getID() + '0'; //send to only sensor created
    to_send[2] = bridge.getID() + '0'; //send to current bridge
    to_send[3] = '1';//cmd = 1

    bridge.send_c(0, (BYTE*)to_send, 4);
    bridge.recv_c_handler(0, bridge_c_handler);
    bridge.recv_c(bridge.getID());




    cout<<endl<<"================= Sensor Node command send/recv test ======================="<<endl<<endl;
    //thread for receiving data?

    //simulate incoming command
    //-----------------control packet--------------------
    to_send[0] = 'c';
    to_send[1] = sensor.getID() + '0';
    //cout<<"sensor id: "<<sensorID<<endl;
    to_send[2] = '1';//cmd = 1
    to_send[3] = '.';
    //---------------------------------------------------
    //BYTE *ptr = to_send;

    cout<< "Sent by bridge to sensor: "<<(BYTE*)to_send<<endl;

    sensor.send_c(0, (BYTE*)to_send, 3); 

    sensor.recv_c_handler(0, sensor_c_handler);
    sensor.recv_c(sensor.getID());//bridge sids for now
    //sensor.setActiveCommand(command);
    //cout<<"Active command: " << sensor.getActiveCommand()<<endl;
    cout<<"---------------------Next command---------------------------"<<endl;
    to_send[2] = '3';//cmd = 1
    sensor.send_c(0, (BYTE*)to_send, 3); //send cmd to sensor using loop back
    sensor.recv_c(sensor.getID());

    cout<<"================= Bridge Node data send/recv test ======================="<<endl;
    int data_size = 4; //4 bytes of data
    BYTE to_send_d[data_size + 3];
    BYTE data[data_size] = {'w','x','y','z'};
    
    //-----------------data packet--------------------
    to_send_d[0] = 'd';
    to_send_d[1] = sensor.getID()+'0';
    to_send_d[2] = data_size +  '0';

    
    for (int i = 3; i<=6;i++){
        to_send_d[i] = data[i-3];

    }

    bridge.send_sd((BYTE*)to_send_d, data_size+3);
    bridge.recv_sd_handler(0, bridge_d_handler);
    bridge.recv_sd(data_size+3);

    cout<<"================= Control Node data send/recv test ======================="<<endl;

    control.send_sd((BYTE*)to_send_d, data_size+3);
    control.recv_sd_handler(0, control_d_handler);
    control.recv_sd(data_size+3);
    cout<<"View data using the user interface below."<<endl;
    sensor.closeGPIO();

    cout<<"================= Sensor data polling test ======================="<<endl;
    while (sensor.isOn()){
        sleep(5);
        cout<<"Polling now. (5 seconds elapsed)"<<endl;
        //CONTINUE HERE

    }

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