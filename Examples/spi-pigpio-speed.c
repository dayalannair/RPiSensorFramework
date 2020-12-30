/*
 * spi-pigpio-speed.c
 * 2016-11-23
 * Public Domain
*/

#include <stdio.h>
#include <stdlib.h>

#include <pigpio.h>

/*
   gcc -pthread -o spi-pigpio-speed spi-pigpio-speed.c -lpigpio

   sudo ./spi-pigpio-speed [bytes [bps [loops] ] ]
*/

#define LOOPS 10000
#define SPEED 1000000
#define BYTES 3

int main(int argc, char *argv[])
{
   int loops=LOOPS;
   int speed=SPEED;
   int bytes=BYTES;
   int i;
   int h;
   double start, diff;
   char buf[16384];


   if (argc > 1) bytes = atoi(argv[1]);
   else printf("sudo ./spi-pigpio-speed [bytes [bps [loops] ] ]\n\n");

   if ((bytes < 1) || (bytes > 16383)) bytes = BYTES;

   if (argc > 2) speed = atoi(argv[2]);
   if ((speed < 32000) || (speed > 250000000)) speed = SPEED;

   if (argc > 3) loops = atoi(argv[3]);
   if ((loops < 1) || (loops > 10000000)) loops = LOOPS;

   if (gpioInitialise() < 0) return 1;

   h = spiOpen(0, speed, 0);

   if (h < 0) return 2;

   start = time_time();

   for (i=0; i<loops; i++)
   {
      spiXfer(h, buf, buf, bytes);
   }

   diff = time_time() - start;

   printf("sps=%.1f: %d bytes @ %d bps (loops=%d time=%.1f)\n",
      (double)loops / diff, bytes, speed, loops, diff);

   spiClose(h);

   gpioTerminate();

   return 0;
}

