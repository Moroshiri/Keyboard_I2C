#include "Keyboard_I2C.h"
#include <Arduino.h>

#if defined(__AVR)

Keyboard_I2C::Keyboard_I2C(uint8_t address)
{
    this->address = address;
    wire = &Wire;
}

bool Keyboard_I2C::begin()
{
    wire->begin();
    writedPins = 0xFF;
    return sendByte(writedPins)==0;
}

uint8_t Keyboard_I2C::sendByte(uint8_t value)
{
  wire->beginTransmission(address);
  wire->write(value);
  return wire->endTransmission();
}

void Keyboard_I2C::setByte(uint8_t value)
{
  sendByte(value);
  writedPins = value;
}

uint8_t Keyboard_I2C::getByte()
{
  #if defined(DEBUG)
  Serial.println(F("Reading"));
  #endif

  uint8_t result;
  wire->requestFrom(address, (uint8_t)1);

  #if defined(DEBUG)
  Serial.println(F("Requested"));
  #endif

  if(wire->available())
    result = wire->read();
  
  #if defined(DEBUG)
  Serial.println(F("Readed"));
  Serial.print("Result: ");
  Serial.println(result);
  #endif

  return result;
}

void Keyboard_I2C::setPin(uint8_t pin, uint8_t value)
{
  uint8_t pinMask = bit(pin);
  if (value)
    writedPins |= pinMask;
  else
    writedPins &= ~pinMask;

  sendByte(writedPins);
}

uint8_t Keyboard_I2C::getPin(uint8_t pin)
{
  return (getByte() & bit(pin)) >> pin;
}

uint16_t Keyboard_I2C::scanKeyboard()
{
    uint16_t keysState = 0;
    for(uint8_t r = 0; r < 4; r++)
    {
        setPin(r + R1, LOW);
        for(uint8_t c = 0; c < 4; c++)
        {
            uint8_t value = getPin(c + C1);
            
            #if defined(TRYKEYS)
            Serial.print("R: ");
            Serial.print(r);
            Serial.print(" C: ");
            Serial.print(c);
            Serial.print(" V: ");
            Serial.println(value);
            #endif

            keysState |= !value << (c + r*4);
        }
        setPin(r + R1, HIGH);
    }
    return keysState;
}

#endif