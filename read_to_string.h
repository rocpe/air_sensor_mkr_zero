/*
 *
 *
 * Local lib for putting read data to string called dataString. Check if you 
 * have all neeeded libs.
 *
 *
*/

#pragma once

/*
 * Needed libs
 */
#include <SPI.h>
#include <SD.h>
#include <Arduino.h>
#include <TinyGPSPlus.h>
#include <SimpleDHT.h>
#include "wiring_private.h"
#include "PMS.h"

#define SEP ";"

void blink(int LED, int INTER, int TIMES);  //blink a led. INTER is time of led on in us
void gpsReadToString(String& dataString);   //get gps reads and put them to dataString
void pms7003ReadToString(String& dataString);//get reads from pms7003 and put them to dataString
void dht11ReadToString(String& dataString); //get dht11 reads and put then to dataString
