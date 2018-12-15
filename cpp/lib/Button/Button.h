#ifndef BUTTON_H
#define BUTTON_H

#include <ArduinoSim.h>

class Button
{
private:
    byte pin;
public:
    Button(byte);
    bool isPressed();
};
#endif
