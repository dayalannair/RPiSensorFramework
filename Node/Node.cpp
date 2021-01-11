#include "Node.hpp"


int Node::getID(){
      return nid;
}

void Node::setActiveCommand(BYTE c){
      activeCommand = (int)c;

}

// handle an incoming control command, may need to forward on
//not sure how the following 3 functions work together. Ask in next meeting.
int Handler(Node node, BYTE *ctr, unsigned int sz)
{
      BYTE type = ctr[0];//indicates that a command is to follow. declare outside fn?
      BYTE command;
      BYTE nodeID;
      if (type == 'c'){
            nodeID = ctr[1];

            if (nodeID == node.getID()){
                  //set the active command which will be executed by sensor
                  node.setActiveCommand(ctr[2]);
                  return 1;
            }
            else{
                  //forward command
                  node.send_c(0,ctr,sz);
                  return 2;
            }
      }
      return 0;
}

void Node::send_c(int id, BYTE *ctr, unsigned sz) //bn = block number -- not used for control?
{
//need to add a bit/byte that indicates this is a control command/not data
    spiXfer(spiHandle, ctr, rx_buffer, 3);
}
     
//both sensors and bridges receive commands but dont send any; only forward commands
void Node::recv_c_handler(int port, NodeControlHandler *handler)
{
      ControlHandler = handler;
      //check buffer. buffer "fills" on each transmit?
      //use spiRead or spiXfer
      spiXfer(spiHandle, rx_buffer, rx_buffer, 1);//send out what is in rx_buffer and replace with newly received data
      //https://www.codeguru.com/cpp/cpp/cpp_mfc/callbacks/article.php/c10557/Callback-Functions-Tutorial.htm



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

void Node::setupIO(int port) //set up gpio given input and output ports
{
      if (gpioInitialise() < 0)
      {
            // pigpio initialisation failed.
      }
      else
      {
            // pigpio initialised okay.
            if (port == 0){
                  spiHandle = spiOpen(port, 64000, 0);//close at end of main()
            }
            
            else if (port == 1){
                  spiHandle = spiOpen(port, 64000, 0);//close at end of main()
            }
            else{
                  cout << "Raspberry Pi requires either port 0 (main SPI) or port 1 (auxiliary SPI)";
            }
            //all functions: http://abyz.me.uk/rpi/pigpio/cif.html#gpioInitialise
      }
}