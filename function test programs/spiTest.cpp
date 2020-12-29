//send out SPI from main port and receive this data via the auxiliary SPI port

#include <pigpio.h>
#include <pthread.h>
#include <iostream>
using namespace std;

int h1 = spiOpen(1, 64000, 0); //sender 
int h2 = spiOpen(2, 64000, 0); //receiver
void *receiveSPI(void*x){
    char received[2]; 
    int count = 1;
    spiRead(h2, received, count);
    cout<<received[count];
    return NULL;
}
int main()
{
    if (gpioInitialise() < 0)
    {
        // pigpio initialisation failed.
    }
    else
    {
        char buffer[1];
        buffer[0] = 'd';
        
        pthread_t threads[1];
        int rc = pthread_create (&threads[1], NULL, receiveSPI, (void *)1); 
        if (rc) {
            cout << "Error:unable to create thread," << rc << endl;
            exit(-1);
        }
        // h1 = spiOpen(1, 64000, 0); //sender 
        // h2 = spiOpen(2, 64000, 0); //receiver

        spiWrite(h1, buffer, 1);
        
        spiClose(h1);
        spiClose(h2);

    }
}