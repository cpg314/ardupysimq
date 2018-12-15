#include "WDT.h"

void delay_wdt(int s)
{
    for (int i(0); i<s; i++)
    {
	delay(1000);
	wdt_reset();
    }
}
