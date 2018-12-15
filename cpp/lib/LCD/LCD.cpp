#include "LCD.h"

LCD::LCD(byte pin)
    : ser(SoftwareSerial(255, pin)), pin(pin)
{
}
void LCD::init()
{
    pinMode(pin, OUTPUT);
    ser.begin(9600);
    clear();   
}
void LCD::enableBacklight(byte brightness)
{
    ser.write(0x7C); //124
    ser.write(140);
    delay(LCD_DELAY);
    /*if (brightness==40 || brightness==73 || brightness==100) ser.print(0x7C);

      switch(brightness)
      {
      case 40:
      ser.print(140);
      delay(100);
      break;
      case 73:
      ser.print(150);
      delay(100);
      break;
      case 100:
      ser.print(157);
      delay(100);
      break;
      }*/
}
void LCD::disableBacklight()
{
    ser.write(0x7C);
    ser.write(128);
    delay(LCD_DELAY);
    clear();
}
void LCD::toogleSplashScreen()
{
    ser.write(0x7C);
    ser.write(0x09);
    delay(LCD_DELAY);
}
void LCD::selectLine1()
{
    ser.write(0xFE);
    ser.write(128);
    delay(LCD_DELAY);
}
void LCD::selectLine2()
{
    ser.write(0xFE);
    ser.write(192);
    delay(LCD_DELAY);
}
void LCD::clear()
{
    ser.write(0xFE);
    ser.write(0x01);
    delay(LCD_DELAY);
}
void LCD::print(char* s)
{
    if (strlen(s)>16) s[16]='\0';
    ser.print(s);
    delay(LCD_DELAY);
}
void LCD::print(char* s, unsigned int i)
{
    if (i==0) selectLine1();
    else selectLine2();
    print(s);
}
void LCD::print(char* line1, char* line2)
{
    selectLine1();
    print(line1);
    selectLine2();
    print(line2);
}
void LCD::reset()
{
    clear();
    disableBacklight();
}
