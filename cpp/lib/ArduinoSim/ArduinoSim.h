#ifndef ARDUINOSIM_H
#define ARDUINOSIM_H

///////////////////////////////////////////////////////////////////////////////
//                               Device mode                                 //
///////////////////////////////////////////////////////////////////////////////
#ifndef SIMULATOR
#include "Arduino.h"
#include <avr/wdt.h>
#include <SPI.h>
class ZMQ
{
};
// Store strings into PROGMEM
extern char F2_buffer[];
#define F2(str) (strcpy_P(F2_buffer, PSTR(str)), F2_buffer)
#else
///////////////////////////////////////////////////////////////////////////////
//                               Simulator mode                              //
///////////////////////////////////////////////////////////////////////////////
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <zmq.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <sys/time.h>

typedef unsigned char byte; //0-255

#define F(X) X

// Pins
enum Mode { INPUT, OUTPUT };
enum Level {HIGH, LOW};
void pinMode(int, Mode);
void digitalWrite(int, Level);
Level digitalRead(int);
int analogRead(int);
void analogWrite(int,int);
void tone(byte pin, unsigned int frequency);
void noTone(byte pin);
// Serial
class SerialClass
{
public:
    void begin(int);
    void println(char*);
    void println(int);
    void print(char*);
};
extern SerialClass Serial, Serial1, Serial2, Serial3;
// Time
extern struct timeval start_time;
void delay(int i);
unsigned long millis();
// Watchdog timers
enum Wdt_mode {WDTO_1S=1, WDTO_2S=2, WDTO_3S=3, WDTO_4S=4, WDTO_8S=8};
void wdt_disable();
void wdt_enable(Wdt_mode);
void wdt_reset();
// SPI
class SPIClass
{
public:
    void begin() {};
};
extern SPIClass SPI;
// ZMQ
class ZMQ
{
private:
    static zmq::context_t* context;
    static zmq::socket_t* socket;
    static bool connected;
public:
    ZMQ();
    ZMQ(const ZMQ&);
    void send(std::string);
    std::string receive();
};
#define F2(X) X

void loop();
void setup();
#endif
#endif
