#include <Arduino.h>
#define TRYKEYS

#include "Keyboard_I2C.h"

#define EXP_ADDR 0x20

Keyboard_I2C keyboard(EXP_ADDR);

void setup()
{
  Serial.begin(115200);
  Serial.println(F("Hello!"));
  while(!keyboard.begin())
  {
    Serial.println("Keyboard communication error!");
    delay(2000);
  }
}

void loop()
{
  Serial.println(keyboard.scanKeyboard());
  delay(1000);
}