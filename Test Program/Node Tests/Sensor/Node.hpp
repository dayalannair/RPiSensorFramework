#ifndef NODE_H
#define NODE_H
#include <pigpio.h>
//#include <pthread.h>
#include <iostream>
using namespace std;
typedef unsigned char BYTE;

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
    typedef int NodeControlHandler(int id, BYTE *ctr, unsigned sz);
    void recv_c_handler(int port, NodeControlHandler);
    void recv_sd_handler(int port, int data, DataHandler *handler);
    void send_sd(BYTE *data, unsigned sz);
    //void outp(int port, BYTE data);
    //void outpd(int port, BYTE *data, unsigned sz);
    void setupIO(int in, int out);
};

#endif