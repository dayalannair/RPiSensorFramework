#include <iostream>
#include <string>
//add these to header file
using namespace std;

class control : public Node
{
private:
    int bridges[3] = [ 0, 0, 0 ]; //Sensor Nodes being Bridged
    int numBridges = 0;           //max of 3 Sensors
    /*    
      1 = start
      2 = stop
      3 = toggle sampling rate?
      4 = display data
      */
    int bid; //Bridge ID
    int commands[4] = {1, 2, 3, 4};
    Data SensorData[]; // array of type Data (see class below)
    //main user interface through this Node
    //array to hold Sensor data: 2D? account for multiple Sensors and readings

public:
    control(int id, int inPort, int outPort)
    {                  //constructor
        isRepo = true; //repo part of control node
        nid = id;
        outputPort = outPort;
        inputPort = inPort;
    }
    //commands affect all Nodes or one in particular?
    void command(int cmd, int sid)
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
            printf("Invalid control command");

        //display data from the repo connected to the control node
        int getData(int samples, int sid)
        { //samples is the number of samples requested, sid is the id of the sensor which produced the samples
        }

        void addBridge(int b)
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

        void inputHandler(int cmd)
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
                cout<<"Invalid input";

            }
        }
    };

    class Data
    {
    private:
        int sensorID;
        int time; //may need string
        int dataSample;

    public:
        string toString()
        {
            return ("Sensor ID: " + sensorID + "\ntime: " + time + "\n Value: " + dataSample);
        }
    };

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
            cout<<"Enter a command \n";
            cout<<"1 - start sampling \n";
            cout<<"2 - stop sampling \n";
            cout<<"3 - change sampling rate \n";
            cout<<"4 - view data \n";
            cin >> userInput;
            //pass command to the node's input handler. can add option for exiting program.
            C1.inputHandler(userInput);


        };