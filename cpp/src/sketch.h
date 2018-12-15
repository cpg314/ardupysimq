#ifndef SKETCH_H
#define SKETCH_H

#include <LCD.h>
#include <Buzzer.h>
#include <Button.h>
#include <Relay.h>
#include <ParallaxRFID.h>
#include <MFRC522RFID.h>
// #include <GSM.h>

#include <math.h>

#include <ArduinoSim.h>
#include <SDSim.h>

#include "config.h"

// Initialize modules
extern LCD lcd;
extern Buzzer buzzer;
extern Button button;
extern Relay relay;
// extern GSM gsm;
// RFID
#if RFID_TYPE == PARALLAX
extern ParallaxRFID rfid;
#else
extern MFRC522RFID rfid;
#endif


#endif
