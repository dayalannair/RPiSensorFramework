/*
Control Node class with main method. This node is the primary interface for the user and allows for commands to be sent to sensor nodes and for a local data repository
Author: Dayalan Nair
Date: December 2020
*/
#include "Control.hpp"

//constructor
Control::Control(int controlID)
{
    isRepo = true; //repo part of control node
    nid = controlID;
    nodeType = 'c';
    //setupIO(0);
}
//commands affect all Nodes or one in particular?

//for now, command affects all sensor nodes belonging to a specified bridge
void Control::command(BYTE cmd, int bridgeID, int sensorID)
{
    bool found = false; // needed for displaying error if command not found
    for (int i = 0; i < 3; i++)
    {
        if (commands[i] == cmd)
        {
            found = true;
            break;
        }
        // send out command to all Bridges which in turn send out to all Sensors
    }
    //if the command is valid, send to output port i.e. bridges
    if (found == true)
    {
        bool found = false;
        int i;
        for (i = 0; i < numBridges; i++)
        {
        //locate/check if bridge ID is valid
            if (bridges[i] == bridgeID)
            {
                //locate port by finding position of id which will be the same position as its corresp. output port
                // send out ctr byte on port b_outPorts[i]
                found = true;
                break;
            }
        }
        if (found == false)
        {
            cout << "Bridge with given ID not found."<<endl;
        }
        else
        {
            BYTE to_send[4];
            //-----------------control packet--------------------
            to_send[0] = 'c';
            to_send[1] = sensorID + '0';
            to_send[2] = bridgeID + '0';
            //cout<<"sensor id: "<<sensorID<<endl;
            to_send[3] = cmd;
            //---------------------------------------------------
            //BYTE *ptr = to_send;

            cout<< "To send: "<<(BYTE*)to_send<<endl;
            send_c(bridgePorts[i], (BYTE*)to_send, 4);//i will be 0 in example
            cout << "Command sent."<<endl;
        }
        
    } //will send out on the output port specified on contruction
    else
    {

        cout<<"Invalid control command"<<endl;
    }
}

void Control::addBridge(int bid, int port)
{
    if (numBridges < 3)
    {
        //add sensor ID and ports to memory (array)
        bridges[numBridges] = bid;
        bridgePorts[numBridges] = port;
        //set up IO for sensor node
        //port must = 0 OR 1 for RPi and a max of 2 bridges.
        if (port < 2 && port>=0){
            setupIO(port);
            cout<<"Bridge with ID: "<<bid<<" added on port: "<<port<<endl;
        }
        numBridges++;
    }
    else
    {
        cout<<"The maximum number of bridges has been reached."<<endl;
    }
}

void Control::saveData(int sensorID,BYTE* time, BYTE* data,  unsigned int sz){
    
    if (numData < 64){
        Data new_data(sensorID, time, data, sz);
        sensorData[numData] = new_data;
        numData++;

    }
    else{
        cout<<"Data array is full. Store data in repository."<<endl;
    }


}

//display data from the repo connected to the control node. Could be improved
// int Control::getData(int samples, int sid)
// { //samples is the number of samples requested, sid is the id of the sensor which produced the samples
//     //loop through entire array (not the most elegant soln). need to handle error if fewer samples in array and therefore if end of array reached before samplesFound == samples
//     int samplesFound = 0;
//     for (int i = 0, i < samplesFound, i++)
//     {
//         if (SensorData[i].getID == sid)
//         {
//             cout << SensorData[i].toString(); //display sensor data
//             samplesFound++;                   //increment no. samples found
//             if (samplesFound == samples)
//             { //exit loop if required samples have been displayed
//                 break;
//             }
//         }
//     }
// }

void Control::displayBridges(){
    cout<<"----------------------Display Bridge IDs----------------------------"<<endl;
    for (int i = 0; i < numBridges; i++){
        cout<<"Bridge "<<i+1<<" ID: "<<bridges[0]<<endl;
    }
}

void Control::inputHandler(BYTE cmd)
{
    int id;
    switch (cmd)
    {
    case SENSOR_ON:{
        cout << "Start command selected. Enter Sensor ID: ";
        cin >> id;
        //send_c(bridges[0], &cmd, 1);//send to first bridge for now
        command(cmd, bridges[0], id);
        break;

    }
        
    case SENSOR_OFF:{
        cout << "Stop command selected. Enter Sensor ID: ";
        cin >> id;
        //send_c(bridges[0], &cmd, 1);//send to first bridge for now
        command(cmd, bridges[0], id);
        break;

    }
        
    case '3':{
        int sRate;
        cout << "Select desired sampling rate: "<<endl<<"3 - 10 000"<<endl<<"4 - 1 000"<<endl<<"5 - 10"<<endl;
        cin >> sRate;
        if (sRate == SAMPLE_10000){

            
        }
        else if (sRate == SAMPLE_1000){


        }
        else if (sRate == SAMPLE_10){


        }
        else{
            cout<<"Invalid selection."<<endl;
        }

        //send_c(bridges[0], &cmd, 1);//send sRate also? or toggle
        break;


    }
        //sampling rate. Easier to use toggle OR use single integer commands for each sampling rate.
        
    case '4':{
        int samples;
        int senseId;                                    //id of sensor whose data is required
        cout << "Enter number of samples to display: "; // Type a number and press enter
        cin >> samples;                                 // Get user input from the keyboard
        cout<<endl<<"Samples requested: "<<samples<<endl;
        for (int i = 0; i < samples; i++)
        {
            if (sensorData[i].getID() == 0){
                cout<<"Only "<<i<<" sample(s) exist in memory."<<endl;
                break;
            }
            else{
                sensorData[i].printSample();
            }
            
        }
        break;
    }
    
    default:
        cout << "Invalid input";
    }
}
//================================== Main function ==================================

//Uncomment and add code (such as that seen in the example "Main.cpp") inside the while loop
//Add handlers/copy from the "Main.cpp" program

//=====================================================================================
// int main()
// {
// ------------------ set up node here ----------------------------------------
//     Control C1(123);
//     char userInput;

//     //turn on sensors with bridge ID 456
//     C1.command('1', 456, 546);

//     bool nodeOn = true;
// -----------------------------------------------------------------------------

//     while (nodeOn)
//     {
//         cout << "Enter a command \n";
//         cout << "1 - start sampling \n";
//         cout << "2 - stop sampling \n";
//         cout << "3 - change sampling rate \n";
//         cout << "4 - view data \n";
//         cout << "q - quit \n"; 
//         cin >> userInput;
//         //pass command to the node's input handler. can add option for exiting program.
//         if (userInput == 'q')
//         {
//             nodeOn = false;
//         }
//         else
//         {
//             C1.inputHandler(userInput); //handler must work with input as string
//         }
//     }
// }