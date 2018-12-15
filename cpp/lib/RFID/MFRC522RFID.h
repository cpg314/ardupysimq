#ifndef MFRC522RFID_H
#define MFRC522RFID_H

#include "RFID.h"
#include "MFRC522.h"

#include <ArduinoSim.h>

class MFRC522RFID: public RFID
{
private:
    char tag[9];
    MFRC522 rfid;
    MFRC522::MIFARE_Key key;
    // Tag length: 4 bytes=4*8=32 bits=8 hex digits
public:
  
    MFRC522RFID(byte rst, byte ss);
    
    char* getTag();
    bool available();
    void enable();

};
#endif
