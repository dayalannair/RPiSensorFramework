#ifndef NODE_H
#define NODE_H
#include <pigpio.h>
//#include <pthread.h>
#include <iostream>
using namespace std;

class Node
{
protected:
    int nid;
    bool isRepo = false;//allows for selecting a repo node
    int outputPort;
    int inputPort;
    bool isOn = false;
    
    int spiHandle;
    char tx_buffer[8];
    char rx_buffer[8]; 

    int nodeType; 
    /*
    1 - control
    2 - bridge 
    3 - sensor
    */

public:
    typedef int NodeControlHandler(int id, byte ctr, unsigned sz);
    recv_c_handler(int port, NodeControlHandler);
    recv_sd_handler(int port, int data, DataHandler *handler);
    send_sd(int data, unsigned sz);
    outp(int port, byte data);
    outpd(int port, byte *data, unsigned sz);
    void Node::setupIO(int in, int out);
};