//Implementation of the sensor node class and sensor reading using pigpio
#include "Sensor.hpp"

Sensor::Sensor(int id, char t, int r)//port can be used to specify control port. using 0 for now
{
      isRepo = false;
      nid = id;
      type = t;
      samplingRate = r;
      setupIO(0);
      setupIO(1);
      nodeType = 's';

}
//get functions will be linked to specific commands sent by the control node
void Sensor::setType(char t)
{
      type = t;
}
char Sensor::getType()
{
      return type;
}
void Sensor::setSamplingRate(int r)
{
      samplingRate = r;
}
int Sensor::getSamplingRate()
{
      return samplingRate;
};
int Sensor::getID(){
      return nid;
}
int Sensor::getActiveCommand(){
      return activeCommand;

}
//run this inside a thread
void Sensor::executeCommand(void* arg){
      switch(activeCommand){
            case 1:
                  on_off = true;
            case 2:
                  on_off = false;
            case 3:
                  samplingRate = 1000;
            case 4:
                  samplingRate = 10000;
            case 5:
                  samplingRate = 10;
            //add more commands here 
            default:
                  activeCommand = 0; //reset active command     

      }
      pthread_exit(NULL);

}
void Sensor::on(){
      //no need for rx thread. can periodically check. 
      // int cmd_thread;
      // pthread_t threads[1];
      // cout<<"thread for executing commands created"<<endl;
      // cmd_thread = pthread_create(&threads[1], NULL, &Sensor::executeCommand , NULL);

      // while(on_off == true){
           
      // }
      //need to void pthread_exit(void *retval);



}

// int main()
// {
//       //dummy data used to set up framework
//       int tempSensorData = 4;
//       //configure input and output ports

//       //convert this node to a sensor node
//       Sensor thisNode(456,(BYTE*)"temp",64000); //789 is bridge ID
//       thisNode.set_on_off(true);
//       while (thisNode.isOn())
//       {
//             //check for received commands
//             if (thisNode.isOn() == true)
//             {
//                   //begin sampling
//                   //send data from sensor node to output port after formatting
//                   //need ADC library
//             }
//             else
//             {
//                    //check for command that turns node on
//             };
//       }
//       gpioTerminate();
// };
