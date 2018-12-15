#ifndef LCD_H
#define LCD_H

#include <ArduinoSim.h>
#include <SoftwareSerialSim.h>

#define LCD_DELAY 50

class LCD
{
private:

    SoftwareSerial ser;
    byte pin;

public:

    LCD(byte pin);

    void enableBacklight(byte brightness=0);
    void disableBacklight();
    void toogleSplashScreen();
    inline void selectLine1();
    inline void selectLine2();
    void clear();
    void reset();
    void init();
    void print(char*);
    void print(char*, unsigned int);
    void print(char*, char*);

};
#endif
