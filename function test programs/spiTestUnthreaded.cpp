//send out SPI from main port and receive this data via the auxiliary SPI port
// TO BUILD

// g++ -o spiTest spiTest.cpp -lpthread -lpigpio -lrt

// TO RUN

// sudo ./spiTest

#include <pigpio.h>
//#include <pthread.h>
#include <iostream>
using namespace std;

int h1; 
//int h2;

void setup(){
    h1 = spiOpen(0, 64000, 0); //sender 
    //h2 = spiOpen(1, 64000, 0); //receiver
}

// void *receiveSPI(void*x){
//     char received[2]; 
//     int count = 1;
//     spiRead(h2, received, count);
//     cout<<received[count];
//     return NULL;
// }
int main()
{
    gpioInitialise();
    if (gpioInitialise() < 0)
    {
        // pigpio initialisation failed.
    }
    else
    {
        setup();
        char tx_buffer[1];
        tx_buffer[0] = 'd';
        char rx_buffer[2]; 
        int count = 1;
        //pthread_t threads[1];
        // int rc = pthread_create (&threads[1], NULL, receiveSPI, (void *)1); 
        // if (rc) {
        //     cout << "Error:unable to create thread," << rc << endl;
        //     exit(-1);
        // }
        // h1 = spiOpen(1, 64000, 0); //sender 
        // h2 = spiOpen(2, 64000, 0); //receiver
        
        //spiWrite(h1, buffer, 1);
        //spiRead(h1, received, count);

        cout<<"Sent "<<tx_buffer[0] << endl;
        spiXfer(h1, tx_buffer, rx_buffer, 1);
        cout<<"Received "<<rx_buffer[0]<< endl;

        
        spiClose(h1);
        //spiClose(h2);
        gpioTerminate();

    }
}