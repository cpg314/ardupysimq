#include "Relay.h"

Relay::Relay(int pin)
    : pin(pin)
{
    pinMode(pin, OUTPUT);
    set(false);
}
void Relay::set(bool b)
{
    if (b)
        digitalWrite(pin, HIGH);
    else
        digitalWrite(pin,LOW);
}
