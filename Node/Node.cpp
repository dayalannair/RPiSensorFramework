#include "Node.hpp"


int Node::getID(){
      return nid;
}

// handle an incoming control command, may need to forward on
//not sure how the following 3 functions work together. Ask in next meeting.
int Handler(int id, Node node, BYTE *ctr, unsigned int sz)
{
      if (node.getID() != id)
      {
            //forward command if Node NOT the target Node
            node.send_c(id, ctr, 1);//need 2 bytes for using control marker
            return 1;
      }
      else
      {
            //switch statement for node to decide on what operation to perform based on a given command
            // switch (id)//use portion of id?
            // {
            // //control node
            // case 1:
            //       //pass;

            // //bridge node
            // case 2:
            //       //forward to sensor node
            //       //send_c();
            // //sensor node
            // case 3:
            //       //perform command
            // }
      }

      return 2;
}

void Node::send_c(int bid, BYTE *ctr, unsigned sz) //bn = block number -- not used for control?
{
//need to add a bit/byte that indicates this is a control command/not data
    spiXfer(spiHandle, ctr, rx_buffer, 1);
}
     



//both sensors and bridges receive commands but dont send any; only forward commands
void Node::recv_c_handler(int port, NodeControlHandler *handler)
{
      ControlHandler = handler;
      //check buffer. buffer "fills" on each transmit?
      //use spiRead or spiXfer
      spiXfer(spiHandle, rx_buffer, rx_buffer, 1);//send out what is in rx_buffer and replace with newly received data
      //not sure of code below
      //https://www.codeguru.com/cpp/cpp/cpp_mfc/callbacks/article.php/c10557/Callback-Functions-Tutorial.htm

      //generates: error: expression list treated as compound expression in functional cast [-fpermissive] on compilation
      //error: invalid cast to function type ‘Node::NodeControlHandler’ {aka ‘int(int, unsigned char*, unsigned int)’}
      //need to use link above to get better understanding of callback functions
      //NodeControlHandler(port, rx_buffer, 1);//want last BYTE received from buffer


} // indicate function to handle an incoming configuration command
void Node::send_sd(BYTE *data, unsigned int sz)
{
      //tx_buffer = data; the data to be transferred could be placed in the transmit buffer
      spiXfer(spiHandle, data, rx_buffer, sz);
}

bool Node::isOn()
{
      return on_off;
}

void Node::set_on_off(bool status){
      on_off = status;
      //or from incoming control cmd
}

//recv sd moved to control and bridge nodes (not needed for sensor node)
void Node::recv_sd_handler(int port, SensorDataHandler *handler)
{
      // tell system what function to call on incoming Sensor data (packets or BYTEs)
      if (isRepo == false) //if Node is Sensor or Bridge, forward
      {
            send_sd(rx_buffer, 1);
      }
      else
      {
            //write data to repository. may not need else statement as the control Node can write data directly from port to repo
      }
}
//send to control/repo Node

// // optional if needed… the develop might just decide to use fwrite or implement the way to talk to a particular port directly in the send_sd function
// outp(int port, BYTE data); // this would just be a wrapper function, would send a data item out a port,  like putc

// outpd(int port, BYTE *data, unsigned sz); // this would just be a wrapper function, would send a data item out a port like fwrite
void Node::setupIO(int port) //set up gpio given input and output ports
{
      if (gpioInitialise() < 0)
      {
            // pigpio initialisation failed.
      }
      else
      {
            // pigpio initialised okay.
            spiHandle = spiOpen(port, 64000, 0);//close at end of main()

            //set up gpio. note that pigpio uses BCM numbering
            //gpioSetMode(in, PI_INPUT);   // Set GPIO17 as input.
            //gpioSetMode(out, PI_OUTPUT); // Set GPIO18 as output.
            //all functions: http://abyz.me.uk/rpi/pigpio/cif.html#gpioInitialise
      }
}