#ifndef SOFTWARESERIAL_H
#define SOFTWARESERIAL_H

#ifndef SIMULATOR
#include <SoftwareSerial.h>
#else
#include <ArduinoSim.h>
#include <string>
#include <iostream>

class SoftwareSerial: public ZMQ
{
private:
    int rx_pin;
    int tx_pin;
    std::string message(std::string, int type);
public:
    SoftwareSerial(int rx_pin, int tx_pin);
    //SoftwareSerial(const SoftwareSerial&);
    void begin(int baudrate);
    void print(std::string);
    void print(int);
    void println(std::string);
    void write(char*);
    void write(int);
    int available();
    char read();
    void flush();
    void listen();
};
#endif
#endif
