//sensor data transmission functions. 
#include <ctime>
#include <iostream>
typedef unsigned char BYTE;

int formatData(BYTE *data){
    //insert function for converting raw data (from sensor or ADC) into an integer value

}

typedef int Sensor::SensorDataHandler(int nid, int bn, BYTE *data, unsigned sz)
{
    int threshold = 50; //e.g. if temp exceeds 50 deg Celsius, send data
    int sample = formatData(data);//e.g. convert data to an integer temperature value
    if (sample > threshold){
        send_sd(outputPort, nid, data, sz);
    }
}

void Node::send_sd(int port, int sid, BYTE *data, unsigned sz)
{
    int send_sd(int port, int sid, byte *data, unsigned sz)
    {
        //packet structure: Node id, size byte, 0 - 255 bytes of data
        switch (port)
        {
        case 0:
        /*case 1: //more cases for more ports
        case 2:
        case 3:*/
        {
            int i;
            char* dt = ctime(&now);
            //-----------packet of data-------------------------------------------------
            rs232tx(port, sid);//sid is 1 byte
            rs232tx(port, sz); //size of data
            for (i = 0; i < sz; i++)
                rs232tx(port, data[i]); // data 0 - 255 bytes
            rs232tx(port, dt); //time data was sampled
            //----------------------------------------------------------------------------
        }
            return sz;// not sure why this must be here
            break;
        case 16:
            FILE *f = fopen("/dev/lp0", "w"); // using Linux standard parallel port driver
            if (f)
            {
                sz = fwrite(data, sz, 1, f);
                fclose(f);
            }
            else
                sz = 0; // indicate error
            return sz;
            break;
        };
        return 0;
    }
}
return sz;
}
void Node::recv_sd_handler(int port, int data, DataHandler *handler)
{
    // tell system what function to call on incoming Sensor data (packets or bytes)
    //needs work. START HERE--------------------------------------------
    if (isRepo == false) //if Node is Sensor or Bridge, forward
    {
        send_sd(outputPort, nid, data, sz); //port is the output port of the node
    }
    else
    {
        //write data to repository. may not need else statement as the control Node can write data directly from port to repo
    }
}