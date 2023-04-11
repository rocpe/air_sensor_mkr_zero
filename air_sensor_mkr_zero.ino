/*
 *
 *
 * Main file for controlling Arduino mkr Zero with gps module, pms7003, dht11
 * and inserted SD card.
 *
 *
*/

#include <SPI.h>
#include <SD.h>
#include <Arduino.h>
#include <TinyGPSPlus.h>
#include <SimpleDHT.h>
#include "wiring_private.h"
#include "PMS.h"
#include "read_to_string.h"
/////////////////////////////////////////////////////////////////////////////////////

//for sd card
const int chipSelect = SDCARD_SS_PIN; 

// setup Serial2 on pins 0 and 1
Uart Serial2 (&sercom3, 0, 1, SERCOM_RX_PAD_1, UART_TX_PAD_0);

// The TinyGPSPlus object
TinyGPSPlus gps ;
static const uint32_t GPSBaud = 9600;

// The PMS object for pms7003 on Serial2
PMS pms(Serial2);
PMS::DATA pmData;

// The SimpleDHT11 object
int pinDHT11 = 9;
SimpleDHT11 dht11(pinDHT11);
/////////////////////////////////////////////////////////////////////////////////////

void setup() {

    //Start serial communication with computer
    Serial.begin(9600);

    //serial for plantower 7003
    Serial2.begin(9600);
    pinPeripheral(0, PIO_SERCOM); //Assign RX function to pin 0
    pinPeripheral(1, PIO_SERCOM); //Assign TX function to pin 1

    //serial for gps
    Serial1.begin(GPSBaud); 

    //set info led
    pinMode(LED_BUILTIN, OUTPUT); 
    digitalWrite(LED_BUILTIN, LOW);

    // see if the card is present and can be initialized:
    blink(LED_BUILTIN, 500, 3);
    delay(1000);
    if (!SD.begin(chipSelect))
    {
        blink(LED_BUILTIN, 500, 2);
        digitalWrite(LED_BUILTIN, HIGH);
        while (1); // don't do anything more:
    }

    blink(LED_BUILTIN, 300, 3);

    //wake pms7003 up
    pms.wakeUp();

    //and wait 30s for stable read
    delay(30000);
}
/////////////////////////////////////////////////////////////////////////////////////

void loop() {

    //create empty string of data
    String dataString = "";

    //check weather gps is available
    while (Serial1.available() > 0)
        gps.encode(Serial1.read());

    //put gps data to string
    gpsReadToString(dataString);
    blink(LED_BUILTIN, 100, 1);

    // put plantower 7003 data to string
    pms7003ReadToString(dataString);
    blink(LED_BUILTIN, 100, 1);

    // put sht11 read to dataString
    dht11ReadToString( dataString);
    blink(LED_BUILTIN, 100, 1);

    // if gps doesnt work 
    if (millis() > 5000 && gps.charsProcessed() < 10) 
        digitalWrite(LED_BUILTIN, HIGH);

    //open file YOUR_FILE.txt for writing
    File dataFile = SD.open("YOUR_FILE.txt", FILE_WRITE);

    // if the file is available, write to it and close and blink 2 times
    if (dataFile)
    {
        dataFile.println(dataString);
        dataFile.close();
        blink(LED_BUILTIN, 500, 2);

        // print to the serial port too:
        Serial.println(dataString);
    }

    //blink 4 times and wait 60 s
    blink(LED_BUILTIN, 300, 4);
    delay(60*1000);
}
/////////////////////////////////////////////////////////////////////////////////////

void SERCOM3_Handler(){//code needed for Serial2 to work
    Serial2.IrqHandler();
}
