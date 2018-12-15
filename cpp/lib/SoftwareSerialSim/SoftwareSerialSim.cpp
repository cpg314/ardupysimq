#include "SoftwareSerialSim.h"

#ifdef SIMULATOR
SoftwareSerial::SoftwareSerial(int rx_pin, int tx_pin)
    : rx_pin(rx_pin), tx_pin(tx_pin)
{
}
// SoftwareSerial::SoftwareSerial(const SoftwareSerial&)
//     : context(1), socket(context, ZMQ_PAIR)
// {}
std::string SoftwareSerial::message(std::string s, int type)
{
    std::ostringstream ss;
    if (type==0) ss<<"SSPINRX-"<<rx_pin;
    else ss<<"SSPINTX-"<<tx_pin;
    ss<<"-"<<s;
    return ss.str().c_str();
}
void SoftwareSerial::begin(int)
{
    print("BEGIN");
}
void SoftwareSerial::print(std::string s)
{
    send(message(s,1));
}
void SoftwareSerial::print(int i)
{
    write(i);
}
void SoftwareSerial::println(std::string s)
{
    send(message(s+'\r',1));
}
void SoftwareSerial::write(char* s)
{
    print(s);
}
void SoftwareSerial::write(int i)
{
    std::ostringstream ss;
    ss<<i;
    print(ss.str());
}
int SoftwareSerial::available()
{
    // SSPINRX-pin-AVAILABLE
    // Query
    send(message("AVAILABLE",0));
    // Get reply
    std::string reply(receive());
    return atoi(reply.c_str());
}
char SoftwareSerial::read()
{
    // SSPINRX-pin-READ
    send(message("READ",0));
    char c(receive().c_str()[0]);
    return c;
}
void SoftwareSerial::flush()
{
    // SSPINRX-pin-FLUSH
    send(message("FLUSH",0));
    // buffer=std::queue<char>();
}
void SoftwareSerial::listen()
{

}
#endif

