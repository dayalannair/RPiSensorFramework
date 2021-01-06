/*
Author: Dayalan Nair
Date: 06/01/2021

Program for testing the Sensor framework on a single Raspberry Pi.
Uses a loopback by connecting the MOSI and MISO pins and by using the same ports across all 3 nodes

*/

#include "Node.cpp"//squiggle because pigpio not on local PC
#include "Sensor.cpp"
#include "Bridge.cpp"
#include "Data.cpp"
#include "Control.cpp"


