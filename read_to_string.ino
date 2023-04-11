#include "read_to_string.h"

void blink(int LED, int INTER, int TIMES)//INTER is time in us, TIMES is how many times led has to blink
{
    for(int i = 0; i<TIMES; i++)
    {
        digitalWrite(LED, HIGH);
        delay(INTER);
        digitalWrite(LED, LOW);
        delay(INTER);
    }
}
/////////////////////////////////////////////////////////////////////////////////////
void gpsReadToString(String& dataString)//code is based on TinyGPSPlus example file 
{
    if (gps.location.isValid())
    {
        dataString += String( gps.location.lat(), 6);
        dataString += SEP;  //every value is seperated by SEP
        dataString += String( gps.location.lng() , 6);
        dataString += SEP;
    }
    else //if values cannot be read then put NA to the dataString
    {
        dataString += String("NA");
        dataString += SEP;
        dataString += String("NA");
        dataString += SEP;
    }

    if (gps.altitude.isValid())
    {
        dataString += String( gps.altitude.meters() );
        dataString += SEP;
    }
    else
    {
        dataString += String("NA");
        dataString += SEP;
    }
    if (gps.date.isValid())
    {
        dataString += String( gps.date.day());
        dataString += "-";
        dataString += String( gps.date.month());
        dataString += "-";
        dataString += String( gps.date.year());
        dataString += SEP;
    }
    else
    {
        dataString += String("NA");
        dataString += SEP;
    }

    if (gps.time.isValid())
    {
        if (gps.time.hour() < 10) dataString += String("0");
        dataString += String(gps.time.hour());
        dataString += ":";
        if (gps.time.minute() < 10) dataString += String("0");
        dataString += String(gps.time.minute());
        dataString += ":";
        if (gps.time.second() < 10) dataString += String("0");
        dataString += String(gps.time.second());
        dataString += SEP;
    }
    else
    {
        dataString += String("NA");
        dataString += SEP;
    }
}
/////////////////////////////////////////////////////////////////////////////////////
void pms7003ReadToString(String& dataString)//code based on example of lib PMS.h
{
    pms.requestRead();
    delay(1000);
    if (pms.readUntil(pmData)) {//if plantower 7003 has new data
        dataString += String(pmData.PM_AE_UG_1_0);
        dataString += SEP;
        dataString += String(pmData.PM_AE_UG_2_5);
        dataString += SEP;
        dataString += String(pmData.PM_AE_UG_10_0);
        dataString += SEP;
    }else{
        dataString += String("NA");
        dataString += SEP;
        dataString += String("NA");
        dataString += SEP;
        dataString += String("NA");
        dataString += SEP;
    }
}
/////////////////////////////////////////////////////////////////////////////////////
void dht11ReadToString(String& dataString)//code based on example file of SimpleDHT.h
{
    byte temperature = 0;
    byte humidity = 0;
    int err = SimpleDHTErrSuccess;
    if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
        dataString += String("NA");
        dataString += SEP;
        dataString += String("NA");
        dataString += SEP;
    }else{
        dataString += String(temperature);
        dataString += SEP;
        dataString += String(humidity);
        dataString += SEP;
    }
}
