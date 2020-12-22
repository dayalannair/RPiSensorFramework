#include "Node.hpp"

// handle an incoming control command, may need to forward on
//not sure how the following 3 functions work together. Ask in next meeting.
typedef int Node::NodeControlHandler(int id, byte ctr, unsigned sz)
{
      //check if the the current node is the target node
      if (nid != id)
      {
            //forward command if Node NOT the target Node
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

void Node::recv_c_handler(int port, NodeControlHandler)
{
      //links port to the handler?

} // indicate function to handle an incoming configuration command

void Node::recv_sd_handler(int port, int data, DataHandler *handler)
// tell system what function to call on incoming Sensor data (packets or bytes)
if (isRepo == false) //if Node is Sensor or Bridge, forward
{
      forward_data(port, data); //port is the output port of the node
}
else
{
      //write data to repository. may not need else statement as the control Node can write data directly from port to repo
}
//send to control/repo Node
// send data out a port via SPI.
void Node::forward_data(int port, int data, unsigned sz)
{
}

// // optional if needed… the develop might just decide to use fwrite or implement the way to talk to a particular port directly in the send_sd function
// outp(int port, byte data); // this would just be a wrapper function, would send a data item out a port,  like putc

// outpd(int port, byte *data, unsigned sz); // this would just be a wrapper function, would send a data item out a port like fwrite
void Node::setupIO(int in, int out) //set up gpio given input and output ports
{
      if (gpioInitialise() < 0)
      {
            // pigpio initialisation failed.
      }
      else
      {
            // pigpio initialised okay.

            //set up gpio. note that pigpio uses BCM numbering
            gpioSetMode(in, PI_INPUT);  // Set GPIO17 as input.
            gpioSetMode(out, PI_OUTPUT); // Set GPIO18 as output.
            //all functions: http://abyz.me.uk/rpi/pigpio/cif.html#gpioInitialise
      }
}