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
}
//commands affect all Nodes or one in particular?

//for now, command affects all sensor nodes belonging to a specified bridge
void Control::command(BYTE cmd, int bid)
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
        send_c(bid, &cmd, 1);
    } //will send out on the output port specified on contruction
    else
    {

        cout<<"Invalid control command";
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
        }
        numBridges++;
    }
    else
    {
        cout<<"The maximum number of bridges has been reached.";
    }
}
void Control::send_c(int bid, BYTE *ctr, unsigned sz) //bn = block number -- not used for control?
{
    bool found = false;
    for (int i; i < numBridges; i++)
    {
        //locate/check if bridge ID is valid
        if (bridges[i] == bid)
        {
            //locate port by finding position of id which will be the same position as its corresp. output port
            // send out ctr byte on port b_outPorts[i]
            found = true;
            break;
        }
    }
    if (found == false)
    {
        cout << "Bridge with given ID not found.";
    }
    else
    {
        spiXfer(spiHandle, ctr, rx_buffer, 1);
        cout << "Command sent.";
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

//int getBridges(){};

void Control::inputHandler(BYTE cmd)
{
    int id;
    switch (cmd)
    {
    case '1':
        cout << "Start command selected. Enter Bridge ID: ";
        cin >> id;
        send_c(bridges[0], &cmd, 1);//send to first bridge for now
        break;

    case '2':
        cout << "Stop command selected. Enter Bridge ID: ";
        cin >> id;
        send_c(bridges[0], &cmd, 1);//send to first bridge for now
        break;

    case '3':
        //sampling rate. Easier to use toggle OR use single integer commands for each sampling rate.
        int sRate;
        cout << "Enter desired sampling rate: ";
        cin >> sRate;
        send_c(bridges[0], &cmd, 1);//send sRate also? or toggle
        break;

    case '4':
        int samples;
        int senseId;                                    //id of sensor whose data is required
        cout << "Enter number of samples to display: "; // Type a number and press enter
        cin >> samples;                                 // Get user input from the keyboard

        for (int i; i < samples; i++)
        {
            cout << SensorData[i].toString(); //see data class below
        }
        break;

    default:
        cout << "Invalid input";
    }
}

int main()
{
    Control C1(123);
    char userInput;

    //turn on sensors with bridge ID 456
    C1.command('1', 456);

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
        }
        else
        {
            C1.inputHandler(userInput); //handler must work with input as string
        }
    }
}