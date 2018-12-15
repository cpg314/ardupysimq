///////////////////////////////////////////////////////////////////////////////
//                                Device mode                                 //
///////////////////////////////////////////////////////////////////////////////
#ifndef SIMULATOR
char F2_buffer[100];
#else
///////////////////////////////////////////////////////////////////////////////
//                               Simulator mode                              //
///////////////////////////////////////////////////////////////////////////////
#include "ArduinoSim.h"

SPIClass SPI;
struct timeval start_time;

// Delays /////////////////////////////////////////////////////////////////////
void delay(int i) // Sleep for i milliseconds
{
    int r(i%1000);
    int q((i-r)/1000);
    usleep(r*1000);
    for (int i(0); i<q; i++)
        sleep(1);
}
unsigned long millis()
{
    struct timeval now;
    gettimeofday(&now, NULL);
    return (now.tv_sec-start_time.tv_sec)*1000
           +(now.tv_usec-start_time.tv_usec)/1000;
}
// Watchdog timers ////////////////////////////////////////////////////////////
void wdt_disable()
{
    ZMQ().send("WDT OFF");
}
void wdt_enable(Wdt_mode mode)
{
    std::ostringstream ss;
    ss<<"WDT ON "<<mode;
    ZMQ().send(ss.str());
}
void wdt_reset()
{
    ZMQ().send("WDT RST");
}
// Pins ///////////////////////////////////////////////////////////////////////
void pinMode(int, Mode) {}
void digitalWrite(int pin, Level level)
{
    std::ostringstream ss;
    ss<<"DPIN"<<pin<<(level==HIGH ? "-1" : "-0" );
    ZMQ().send(ss.str());
}
Level digitalRead(int pin)
{
    ZMQ z;
    std::ostringstream ss;
    ss<<"DPIN"<<pin<<"-R";
    ZMQ().send(ss.str());
    if (z.receive()=="HIGH") return HIGH;
    return LOW;
}
void tone(byte pin, unsigned int frequency)
{
    analogWrite(pin,frequency);
}
void noTone(byte pin)
{
    analogWrite(pin,0);
}
// Read analog pin
int analogRead(int pin)
{
    ZMQ z;
    std::ostringstream ss;
    ss<<"APIN"<<pin;
    z.send(ss.str());
    return atoi(z.receive().c_str());
}
void analogWrite(int pin, int value)
{
    ZMQ z;
    std::ostringstream ss;
    ss<<"APIN"<<pin<<"-"<<value;
    z.send(ss.str());
}
// Serial /////////////////////////////////////////////////////////////////////
void SerialClass::begin(int i)
{
}
void SerialClass::print(char* s)
{
    std::cout<<s;
}
void SerialClass::println(char* s)
{
    std::cout<<s<<std::endl;
}
void SerialClass::println(int s)
{
    std::cout<<s<<std::endl;
}
SerialClass Serial, Serial1, Serial2, Serial3;
// ZMQ ////////////////////////////////////////////////////////////////////////
zmq::context_t* ZMQ::context=0;
zmq::socket_t* ZMQ::socket=0;
bool ZMQ::connected=false;
// Connection
ZMQ::ZMQ()
{
    if (!connected)
    {
        context=new zmq::context_t(1);
        socket=new zmq::socket_t(*context, ZMQ_PAIR);
        std::cout<<"Connecting to simulator"<<std::endl;
        socket->connect("tcp://localhost:55");
        std::cout<< "Connected"<<std::endl;
        connected=true;
    }
}
ZMQ::ZMQ(const ZMQ&)
{}
// Send
void ZMQ::send(std::string s)
{
    const char* s2=s.c_str();
    zmq::message_t request(strlen(s2));
    memcpy(request.data(),s2,strlen(s2));
    socket->send(request);

}
// Receive
std::string ZMQ::receive()
{
    zmq::message_t reply;
    socket->recv(&reply);
    return std::string(static_cast<char*>(reply.data()), reply.size());
}
#endif
