#ifndef RFID_H
#define RFID_H

#include <ArduinoSim.h>

class RFID
{
protected:
    int tag_length;
public:
    RFID(byte tag_length);
    virtual char* getTag()=0;
    virtual bool available()=0;
    void flush() {};
    void enable() {};
    void disable() {};
    virtual void init() {};
    bool enabled;
};
#endif
