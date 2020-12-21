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

public:
    typedef int NodeControlHandler(int id, byte ctr, unsigned sz);
    send_c(int bn, byte *ctr, unsigned sz);
    recv_c_handler(int port, NodeControlHandler);
    recv_sd_handler(int port, int data, DataHandler *handler);
    forward_data(int port, int data, unsigned sz);
    outp(int port, byte data);
    outpd(int port, byte *data, unsigned sz);
};