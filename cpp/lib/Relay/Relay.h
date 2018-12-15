#ifndef RELAY_H
#define RELAY_H

#include <ArduinoSim.h>

class Relay: public ZMQ
{
private:
    int pin;
public:
    Relay(int);
    void set(bool);
};

#endif
