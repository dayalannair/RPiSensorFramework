//sensor data transmission functions.

//sending data using ports 0 - 3
//receiving data using ports 4 - 6

#include <ctime>
#include <iostream>
#include "Data.hpp"
#include "Data.cpp"
typedef unsigned char BYTE;

//array of data objects
Data SensorData[100];
int pos = 0;
int formatData(BYTE *data)
{
    //insert function for converting raw data (from sensor or ADC) into an integer value
    //e.g. formula for converting temp from ADC (See EEE3096S prac + add here)
}

typedef int SensorDataHandler(int nid, int bn, BYTE *data, unsigned sz)
{
    BYTE *rawSample = 0;
    //collate parts of data into single sample
    if (bn != sz)
    {
        rawSample += data;
    }
    else
    {
        int threshold = 50;                 //e.g. if temp exceeds 50 deg Celsius, send data
        int sample = formatData(rawSample); //e.g. convert data to an integer temperature value
        if (sample > threshold)
        {
            send_sd(outputPort, nid, data, sz);
        }
    }
}

int send_sd(int port, int sid, BYTE *data, unsigned sz)

{
    //packet structure: Node id, size byte, 0 - 255 bytes of data
    switch (port)
    {
    case 0:
        /*case 1: //more cases for more ports
        case 2:
        case 3:*/
        {
            int bn;
            char *dt = ctime(&now);
            //-----------packet of data-------------------------------------------------
            rs232tx(port, sid); //sid is 1 byte
            rs232tx(port, sz);  //size of data
            for (bn = 0; bn < sz; bn++)
                rs232tx(port, data[bn]); // data 0 - 255 bytes

            rs232tx(port, dt); //time data was sampled
            //----------------------------------------------------------------------------
        }
        return sz; // not sure why this must be here
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
    default:
        return 1; //error
        cout << "Invalid port";
    }
    return 0;
}

void Node::recv_sd_handler(int port, DataHandler *handler)
{
    switch (port)
    {
    //---------------------sensor data received by bridge node--------------------------------
    case 4:
        /*case 5: //more cases for more sensor ports
        case 6:
        */
        {
            BYTE *data = 3242352;//read from SPI sensor buffer
            int bridgeID = data[0]; //read ID from data packet. block number 0.
            int blockNum = 1;
            int sz = 3; //e.g. size of data is 3 bytes
            for (i = 0; i < sz; i++)
            {
                //pass blocks of data (i.e. the rest of the packet incl time and size bytes of the data sample) to handler. could pass entire thing?
                //this method required for reading data from bufffers one byte at a time?
                handler(bridgeID, blockNum, data[blockNum], sz);
                blockNum++;
            }
        }
        return sz; // not sure why this must be here
        break;

    //---------------------sensor data received by control node------------------------------
    //port is repository port
    case 15:
    {
        //break up into id, time, sample
        int id = 0;
        int sample = 0;
        int time = 0;
        SensorData[pos] = Data(id, time, sample);
        pos++;
    }
        
    }
default:
    cout << "Invalid port";

    return 0;
}