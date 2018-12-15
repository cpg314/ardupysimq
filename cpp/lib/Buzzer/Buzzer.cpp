#include "Buzzer.h"

#include <WDT.h>

Buzzer::Buzzer(int pin)
    : pin(pin)
{
}
void Buzzer::play(unsigned int frequency, unsigned long duration)
{
    tone(pin,frequency);
    if (duration>1000)
    {
	delay_wdt(duration/1000);
	delay(duration%1000);
    }
    else delay(duration);
    noTone(pin);
}
void Buzzer::beeps(unsigned int frequency, byte number, unsigned int d1, unsigned int d2)
{
    for (byte i(0); i<number; i++)
    {
	play(frequency,d1);
	delay(d2);
    }
}
