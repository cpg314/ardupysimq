#ifndef CONFIG_H
#define CONFIG_H

#define BUZZER_PIN 8
#define LCD_PIN 44
#define BUTTON_PIN 30
#define SENSOR_PIN 9
#define RELAY_PIN 22
// RFID
#define RFID_TYPE PARALLAX
// #define RFID_TYPE MFRC522
#define RFID_PIN_ENABLE 45 // Parallax
#define RFID_PIN_OUT 10 // Parallax
#define RFID_PIN_RST 38 // MFRC522
#define RFID_PIN_SS 26 // MFRC522
// GSM
#define GSM_PIN_RX 15
#define GSM_PIN_TX 14
#define GSM_PIN_RST 36
// SD
#define SD_PIN 41

#endif
