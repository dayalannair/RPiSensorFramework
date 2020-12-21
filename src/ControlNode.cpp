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
void Control::command(int cmd, int sid)
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
        send_c()
    } //will send out on the output port specified on contruction
    else
    {

        printf("Invalid control command");
    }
}

//display data from the repo connected to the control node
int Control::getData(int samples, int sid)
{ //samples is the number of samples requested, sid is the id of the sensor which produced the samples
}

void Control::addBridge(int b)
{ //connect a Sensor Node to the Bridge Node
    if (numBridges < 3)
    {
        bridges[numBridges] = b;
        numBridges++;
    }
    else
    {
        printf("The maximum number of bridges has been reached.")
    }
}

//int getBridges(){};

void Control::inputHandler(int cmd)
{
    switch (cmd)
    {
    case 1:
        break;

    case 2:
        break;

    case 3:
        break;

    case 4:
        int samples;
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
    control C1(123, 34);
    int userInput;

    //turn on sensor with ID 456
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