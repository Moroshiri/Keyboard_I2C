#include <Arduino.h>
#include <Wire.h>

#define EXP_ADDR 0x20
#define R1 4
#define R2 5
#define R3 6
#define R4 7
#define C1 0
#define C2 1
#define C3 2
#define C4 3

#define TRYKEYS

TwoWire wire;

void setByte(uint8_t value);
uint8_t getByte();
void setPin(uint8_t pin, uint8_t value);
uint8_t getPin(uint8_t pin);

uint8_t writedPins;

uint16_t scanKeyboard();

void setup()
{
  Serial.begin(115200);
  Serial.println(F("Hello!"));

  wire.begin();
  setByte(0xFF);
}

void loop()
{
  // setByte(!getByte());
  // delay(1000);

  Serial.println(scanKeyboard());
  delay(1000);
}

void sendByte(uint8_t value)
{
  wire.beginTransmission(EXP_ADDR);
  wire.write(value);
  wire.endTransmission();
}

void setByte(uint8_t value)
{
  sendByte(value);
  writedPins = value;
}

uint8_t getByte()
{
  #if defined(DEBUG)
  Serial.println(F("Reading"));
  #endif

  uint8_t result;
  wire.requestFrom(EXP_ADDR, 1);

  #if defined(DEBUG)
  Serial.println(F("Requested"));
  #endif

  if(wire.available())
    result = wire.read();
  
  #if defined(DEBUG)
  Serial.println(F("Readed"));
  Serial.print("Result: ");
  Serial.println(result);
  #endif

  return result;
}

void setPin(uint8_t pin, uint8_t value)
{
  uint8_t pinMask = bit(pin);
  if (value)
    writedPins |= pinMask;
  else
    writedPins &= ~pinMask;

  sendByte(writedPins);
}

uint8_t getPin(uint8_t pin)
{
  return (getByte() & bit(pin)) >> pin;
}

uint16_t scanKeyboard()
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














// #include <Arduino.h>
// #include "Keyboard_I2C.h"

// #define R1 2
// #define R2 3
// #define R3 4
// #define R4 5
// #define C1 6
// #define C2 7
// #define C3 8
// #define C4 9

// //Keyboard_I2C keyboard(0x20);

// uint16_t scanKeyboard()
// {
//    uint16_t keysState = 0;
//     for(uint8_t r = 0; r < KEY_HEIGHT; r++)
//     {
//         digitalWrite(r + R1, LOW);
//         for(uint8_t c = 0; c < KEY_WIDTH; c++)
//         {
//             uint8_t value = digitalRead(c + C1);
            
//             Serial.print("R: ");
//             Serial.print(r);
//             Serial.print(" C: ");
//             Serial.print(c);
//             Serial.print(" V: ");
//             Serial.println(value);

//             keysState |= !value << (c + r*KEY_HEIGHT);
//         }
//         digitalWrite(r + R1, HIGH);
//     }
//     return keysState;
// }

// void setup()
// {
//   Serial.begin(9600);

//   pinMode(R1, OUTPUT);
//   pinMode(R2, OUTPUT);
//   pinMode(R3, OUTPUT);
//   pinMode(R4, OUTPUT);
//   pinMode(C1, INPUT_PULLUP);
//   pinMode(C2, INPUT_PULLUP);
//   pinMode(C3, INPUT_PULLUP);
//   pinMode(C4, INPUT_PULLUP);

//   digitalWrite(R1, HIGH);
//   digitalWrite(R2, HIGH);
//   digitalWrite(R3, HIGH);
//   digitalWrite(R4, HIGH);

//   // while(!keyboard.begin())
//   // {
//   //   Serial.println(F("Keyboard begin failed!"));
//   //   delay(2000);
//   // }
// }

// void loop()
// {
//   Serial.println(scanKeyboard());
//   delay(1000);
// }