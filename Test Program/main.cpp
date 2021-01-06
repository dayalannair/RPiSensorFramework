#include "main.hpp"

int main(){

    //create 3 node objects
    //using spi pins as ports
    //sid = 1, bid = 2, cid = 3
    Sensor sensor(1, 2, "temp", 10, 19, 21);
    Bridge bridge(2, 19, 21); //may need to modify to require a specified control port
    Control control(3, 19, 21);

    //connect nodes
    control.addBridge(2, 19, 21);
    bridge.addSensor(1, 19, 21);

    //verify
    bridge.displaySensorIDs();

    //start
    //requires control handler to be complete
    control.command(1, 2);//pass command '1' to bridge id = 2. need to complete this fn




}