#include "ParallaxRFID.h"

ParallaxRFID::ParallaxRFID(byte enable, byte sout)
    : ser(SoftwareSerial(sout, 255)), offset(0), enablePin(enable), soutPin(sout), RFID(11)
{
}
void ParallaxRFID::init()
{
    pinMode(enablePin, OUTPUT);
    ser.begin(2400);
}
void ParallaxRFID::enable()
{
    digitalWrite(enablePin, LOW);
    enabled=true;
}
void ParallaxRFID::flush()
{
    for (int i(0); i<11; i++) tag[i]=0;
    ser.flush();
}
void ParallaxRFID::disable()
{
    digitalWrite(enablePin, HIGH);
    enabled=false;
}
char* ParallaxRFID::getTag()
{
    return tag;
}
bool ParallaxRFID::available()
{
    if (ser.available()<=0) return false;
    
    // If new data is available
    if (offset>tag_length)
    {
	// Buffer overflow
	offset=0;
    }
    // Read character
    char c=ser.read();
    if (c==START_BYTE)
    {
	offset=0; // Return to beginning
    }
    else if (c==STOP_BYTE)
    {
	tag[offset]='\0'; // End string
	offset=0;
	return true;
    }
    else
    {
	tag[offset]=c;
	offset++;
    }
    return false;
}
