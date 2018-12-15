#include "Button.h"

Button::Button(byte pin):
    pin(pin)
{
    pinMode(pin, INPUT);
}
bool Button::isPressed()
{
    return digitalRead((int)pin)==HIGH;
}
