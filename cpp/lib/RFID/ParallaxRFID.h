#ifndef PARALLAXRFID_H
#define PARALLAXRFID_H

#include "RFID.h"

#include <ArduinoSim.h>
#include <SoftwareSerialSim.h>

#define START_BYTE 0x0A
#define STOP_BYTE 0x0D

class ParallaxRFID: public RFID
{
private:
  
    SoftwareSerial ser;
    char tag[11];
    int offset;
    byte enablePin;
    byte soutPin;
  
public:
  
    ParallaxRFID(byte enable, byte sout);
	
    void enable();
    void flush();
    void disable();
    char* getTag();
    bool available(); // reads new data
    void init();

};
#endif
