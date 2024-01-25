#ifndef Keyboard_I2C_h
#define Keyboard_I2C_h

#include <Wire.h>

#define KEY_WIDTH 4
#define KEY_HEIGHT 4
#define KEY_BUTTONS 16

#define R1 4
#define R2 5
#define R3 6
#define R4 7
#define C1 0
#define C2 1
#define C3 2
#define C4 3

class Keyboard_I2C
{
public:
    Keyboard_I2C(uint8_t address);

    bool begin();
    uint16_t scanKeyboard();

private:
    uint8_t address;
    uint8_t writedPins;
    TwoWire* wire;

    uint8_t sendByte(uint8_t value);
    void setByte(uint8_t value);
    uint8_t getByte();
    void setPin(uint8_t pin, uint8_t value);
    uint8_t getPin(uint8_t pin);
};

#endif