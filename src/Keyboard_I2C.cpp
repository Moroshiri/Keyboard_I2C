#include "Keyboard_I2C.h"

Keyboard_I2C::Keyboard_I2C(uint8_t address) : _expander(new PCF8574(address)), _keysState(0)
{ }

bool Keyboard_I2C::begin()
{
    _expander->pinMode(P0, OUTPUT, LOW);
    _expander->pinMode(P1, OUTPUT, LOW);
    _expander->pinMode(P2, OUTPUT, LOW);
    _expander->pinMode(P3, OUTPUT, LOW);
    _expander->pinMode(P4, INPUT);
    _expander->pinMode(P5, INPUT);
    _expander->pinMode(P6, INPUT);
    _expander->pinMode(P7, INPUT);

    return _expander->begin();
}

uint16_t Keyboard_I2C::getKeysState() const
{
    return _keysState;
}

void Keyboard_I2C::scanKeyboard()
{
    _keysState = 0;
    for(uint8_t r = 0; r < KEY_HEIGHT; r++)
    {
        _expander->digitalWrite(r, HIGH);
        for(uint8_t c = 0; c < KEY_WIDTH; c++)
        {
            uint8_t value = _expander->digitalRead(c + P4);
            
            Serial.print("R: ");
            Serial.print(r);
            Serial.print(" C: ");
            Serial.print(c);
            Serial.print(" V: ");
            Serial.println(value);

            _keysState |= value << (c + r*KEY_HEIGHT);
        }
        _expander->digitalWrite(r, LOW);
    }
}