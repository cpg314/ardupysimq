#ifndef BUZZER_H
#define BUZZER_H

#include <ArduinoSim.h>

#include "Pitches.h"

class Buzzer: public ZMQ
{
private:
    int pin;
public:
    Buzzer(int);
    void play(unsigned int frequency, unsigned long duration);
    void beeps(unsigned int frequency, byte number, unsigned int d1, unsigned int d2);
};

#endif
