#include <iostream>
#include <string>
#include "Node.cpp"
//add these to header file
using namespace std;

Control::control(int id, int inPort, int outPort)
{                  //constructor
    isRepo = true; //repo part of control node
    nid = id;
    outputPort = outPort;
    inputPort = inPort;
}
//commands affect all Nodes or one in particular?

//for now, command affects all sensor nodes belonging to a specified bridge
void Control::command(int cmd, int bid)
{
    bool found = false;
    for (int i = 0; i < 3; i++)
    {
        if (array[i] == itemToFind)
        {
            found = true;
            break;
        }
        // send out command to all Bridges which in turn send out to all Sensors
    }
    //if the command is valid, send to output port i.e. bridges
    if (found == true)
    {
        send_c(ouputPort, bid, )
    } //will send out on the output port specified on contruction
    else
    {

        printf("Invalid control command");
    }
}
void addBridge(int bid, int in, int out)
{
    if (numBridges < 3)
    {
        //add sensor ID and ports to memory (array)
        bridges[numBridges] = bid;
        b_inPorts[numBridges] = in;
        b_outPorts[numBridges] = out;
        //set up IO for sensor node
        setupIO(out, in);
        numBridges++;
    }
    else
    {
        printf("The maximum number of bridges has been reached.")
    }
}
void Control::send_c(int bid, byte *ctr, unsigned sz) //bn = block number -- not used for control?
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
        cout << "Command sent.";
    }

}
int Data::getID(){

    return sensorID    
}
//display data from the repo connected to the control node
int Control::getData(int samples, int sid)
{ //samples is the number of samples requested, sid is the id of the sensor which produced the samples

}

//int getBridges(){};

void Control::inputHandler(int cmd)
{
    switch (cmd)
    {
    case 1:
        int id;
        cout<<"Start command selected. Enter Bridge ID: ";
        cin>> id;
        send_c(id, 1); //unsigned sz?
        break;

    case 2:
        int id;
        cout<<"Stop command selected. Enter Bridge ID: ";
        cin>> id;
        send_c(id, 2); //unsigned sz?
        break;
        break;

    case 3:
    //sampling rate
        break;

    case 4:
        int samples;
        int senseId; //id of sensor whose data is required
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
//need a separate header file?
string Data::toString()
{
    return ("Sensor ID: " + sensorID + "\ntime: " + time + "\n Value: " + dataSample);
}

int main()
{
    control C1(123, 16, 26);
    int userInput;

    //turn on sensors with bridge ID 456
    C1.command(1, 456);

    //thread for receiving data?
    bool nodeOn = True;
    while (nodeOn)
    {
        cout << "Enter a command \n";
        cout << "1 - start sampling \n";
        cout << "2 - stop sampling \n";
        cout << "3 - change sampling rate \n";
        cout << "4 - view data \n";
        cin >> userInput;
        //pass command to the node's input handler. can add option for exiting program.
        C1.inputHandler(userInput);
    };