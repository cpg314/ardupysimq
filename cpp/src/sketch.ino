#include "sketch.h"

// Initialize modules
LCD lcd(LCD_PIN);
Buzzer buzzer(BUZZER_PIN);
Button button(BUTTON_PIN);
Relay relay(RELAY_PIN);
#if RFID_TYPE == PARALLAX
ParallaxRFID rfid(RFID_PIN_ENABLE,RFID_PIN_OUT);
#else
MFRC522RFID rfid(RFID_PIN_RST, RFID_PIN_SS);
#endif

void setup()
{
    // Serial
    Serial.begin(9600);
    Serial.println("Serial on");
    // SD
    SD.begin(SD_PIN);
    // LCD
    lcd.init();
    lcd.enableBacklight();
    lcd.print(F2("Line 1"), F2("Line 2"));
    // RFID
    rfid.init();
    rfid.enable();
    // Watchdog timer
    // wdt_enable(WDTO_4S);
}
// Main loop
void loop()
{
    if (button.isPressed())
    {
    	relay.set(true);
    }
    else
    {
    	relay.set(false);
    }
    if (rfid.available())
    {
	buzzer.beeps(1760,2,300,500);
	Serial.println(rfid.getTag());
	Serial.println(analogRead(SENSOR_PIN));
	rfid.flush();
    }
}
#ifdef SIMULATOR
int main()
{
    gettimeofday(&start_time, NULL);
    setup();
    while(true)
    {
	loop();
	delay(5);
    }
    return 0;
}
#endif
