#ifndef NODE_H
#define NODE_H

class Node
{
protected:
    int nid;
    bool isRepo = false;
    int outputPort;
    int inputPort;
    bool isOn = false;
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