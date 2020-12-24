//test send_c and recv_c functions
#include "serialib.cpp"
#include <pigpio.h>
typedef unsigned char BYTE;

void setupIO(int in, int out) //set up gpio given input and output ports
{
      if (gpioInitialise() < 0)
      {
            // pigpio initialisation failed.
      }
      else
      {
            // pigpio initialised okay.

            //set up gpio. note that pigpio uses BCM numbering
            gpioSetMode(in, PI_INPUT);   // Set GPIO17 as input.
            gpioSetMode(out, PI_OUTPUT); // Set GPIO18 as output.
            //all functions: http://abyz.me.uk/rpi/pigpio/cif.html#gpioInitialise
      }
}

void send_c(int bid, BYTE *ctr, unsigned sz) //bn = block number -- not used for control?
{
    bool found = false;
    for (int i; i < numBridges; i++)
    {
        //locate/check if bridge ID is valid
        if (bridges[i] == bid)
        {
            //locate port by finding position of id which will be the same position as its corresp. output port
            // send out ctr BYTE on port b_outPorts[i]
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
            switch (nodeType)
            {
            //control node
            case 1:
                  pass;

            //bridge node
            case 2:
                  //forward to sensor node
                  send_c();
            //sensor node
            case 3:
                  //perform command
            }
      }
}
void recv_c_handler(int port, NodeControlHandler)
{
      //links port to the handler?

} // indicate function to handle an incoming configuration command