#include "MFRC522RFID.h"

MFRC522RFID::MFRC522RFID(byte rst, byte ss)
    : rfid(ss, rst), RFID(ss)
{
    // Set key
    for (byte i(0); i < 6; i++) key.keyByte[i] = 0xFF;
}
void MFRC522RFID::enable()
{
    SPI.begin();
    rfid.PCD_Init();
    rfid.PCD_DumpVersionToSerial();
}
char* MFRC522RFID::getTag()
{
    tag[0]='\0';
    for (int i(0); i<4; i++)
	sprintf(tag+strlen(tag),"%hhX",rfid.uid.uidByte[i]);
    return tag;
}

bool MFRC522RFID::available()
{
  if (!rfid.PICC_IsNewCardPresent())
      return false;
  if ( ! rfid.PICC_ReadCardSerial())
      return false;
  return true;
}
