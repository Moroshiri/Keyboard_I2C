#ifndef Keyboard_I2C_h
#define Keyboard_I2C_h

#include <PCF8574.h>

#define KEY_WIDTH 4
#define KEY_HEIGHT 4
#define KEY_BUTTONS 16

class Keyboard_I2C
{
public:
    Keyboard_I2C(uint8_t address);

    bool begin();
    uint16_t getKeysState() const;
    void scanKeyboard();

private:
    PCF8574* _expander;
    uint16_t _keysState;
};

#endif