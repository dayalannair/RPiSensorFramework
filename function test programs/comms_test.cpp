//test send_c and recv_c functions
#include "comms_test.hpp"

void setupIO(int in, int out)
{
    if (gpioInitialise() < 0)
    {
        // pigpio initialisation failed.
    }
    else
    {
        gpioSetMode(in, PI_INPUT);
        gpioSetMode(out, PI_OUTPUT);
    }
}

send_c(int port, int bn, BYTE ctr) //bn = block number -- not used for control?
{
    switch (port)
    {
    case 0: /*case 1: case 2: case 3:*/
    {       //more cases for more ports
        //use library for a comms device e.g.:
        rs232tx(port, ctr); // use custom-implemented routine to send byte out rs232
        break;
        //taken from send_sd
    case 16:
        FILE *f = fopen("/dev/lp0", "w"); // using Linux standard parallel port driver
        if (f)
        {
            sz = fwrite(data, sz, 1, f);
            fclose(f);
        }
        else
            sz = 0; // indicate error
        return sz;
        break;
    };
        return 0;
    }

    // {
    //     bool found = false;
    //     for (int i; i < numBridges; i++)
    //     {
    //         //locate/check if bridge ID is valid
    //         if (bridges[i] == bid)
    //         {
    //             //locate port by finding position of id which will be the same position as its corresp. output port
    //             // send out ctr BYTE on port b_outPorts[i]
    //             found = true;
    //             break;
    //         }
    //     }
    //     if (found == false)
    //     {
    //         cout << "Bridge with given ID not found.";
    //     }
    //     else
    //     {
    //         cout << "Command sent.";
    //     }
    // }

    typedef int NodeControlHandler(int id, BYTE ctr, unsigned sz)
    {
        //check if the the current node is the target node
        if (nid != id)
        {
            //forward command if Node NOT the target Node
            //this fn is in Control!
            send_c(outputPort, bn, ctr);
        }
        else
        {
            //switch statement for node to decide on what operation to perform based on a given command
            switch (ctr)
            {
            //start
            case 1:
                pass;
                //begin sampling from sensor

            //stop
            case 2:

            //sampling rate
            case 3:
                Sensor.setSamplingRate(int x);

            }
        }
    }
    void recv_c_handler(int port, NodeControlHandler)
    {
        

    } // indicate function to handle an incoming configuration command