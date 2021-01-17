#ifndef NODE_H
#define NODE_H
#include <pigpio.h>
#include <pthread.h>
#include <iostream>
using namespace std;
typedef char BYTE;//spiXfer uses char* not unsigned char

typedef int SensorDataHandler(int nid, int bn, BYTE *data, unsigned int sz); 
typedef int NodeControlHandler(int id, BYTE *ctr, unsigned int sz);

class Node
{
protected:
    int nid;
    bool isRepo = false;//allows for selecting a repo node
    bool on_off = false;
    int ports[2] = { 0, 0};  //1 for sensor, 1 for control
    int spiHandle;
    int spiHandleAux;
    char tx_buffer[8];
    char rx_buffer[8]; 
    NodeControlHandler * ControlHandlers[256]; // assuming only 16 ports IDs 0..15
    SensorDataHandler *DataHandler;
    int nodeType; 
    int activeCommand;
    /*
    1 - control
    2 - bridge 
    3 - sensor
    */

public:
    void recv_c_handler(int port, NodeControlHandler *handler); //use int in place of handler
    void recv_sd_handler(int port, SensorDataHandler *handler);
    void recv_c(int* sids);
    void send_c(int port, BYTE *ctr, unsigned sz);
    void send_sd(BYTE *data, unsigned sz);
    bool isOn();
    void set_on_off(bool status);
    void setupIO(int port);
    int getID();
    void setActiveCommand(int c);
    void closeGPIO();
    char* getRxBuffer();
};

#endif