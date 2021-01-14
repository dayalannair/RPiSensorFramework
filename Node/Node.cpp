#include "Node.hpp"


int Node::getID(){
      return nid;
}

void Node::setActiveCommand(BYTE c){
      activeCommand = (int)c;

}


void Node::send_c(int port, BYTE *ctr, unsigned sz) //bn = block number -- not used for control?
{
//need to add a bit/byte that indicates this is a control command/not data
    spiXfer(spiHandle, ctr, rx_buffer, 3);
}
     
//both sensors and bridges receive commands but dont send any; only forward commands
void Node::recv_c_handler(int port, NodeControlHandler *handler)
{
      if (port>=0 && port<=15){
            ControlHandlers[port] = handler; //SPI port either 0 or 1
      } 

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

char *Node::getRxBuffer(){
      char* rx = rx_buffer;
      return rx;

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
            cout<<"Pigpio initialisation failed."<<endl;
      }
      else
      {
            // pigpio initialised okay.
            //cout<<"Pigpio initialised."<<endl;
            if (port == 0){
                  spiHandle = spiOpen(port, 64000, 0);//close at end of main()
            }
            
            else if (port == 1){
                  spiHandleAux = spiOpen(port, 64000, 0);//close at end of main()
            }
            else{
                  cout << "Raspberry Pi requires either port 0 (main SPI) or port 1 (auxiliary SPI)";
            }
            //all functions: http://abyz.me.uk/rpi/pigpio/cif.html#gpioInitialise
      }
}

void Node::closeGPIO(){
      gpioTerminate();
}