/*
 * stkbd.cpp - a library to interface with an Atari ST keyboard.
 * Written by Ada Freeman (iLambda2), December 2017.
 * Release into public domain.
 */

#include "stkbd.h"


// PS/2 set 1 to set 2 map
extern uint8_t ps2set1to2[] = {
  0x00  /* 0 */,
  0x76  /* 1 */,
  0x16  /* 2 */,
  0x1E  /* 3 */,
  0x26  /* 4 */,
  0x25  /* 5 */,
  0x2E  /* 6 */,
  0x36  /* 7 */,
  0x3D  /* 8 */,
  0x3E  /* 9 */,
  0x46  /* A */,
  0x45  /* B */,
  0x4E  /* C */,
  0x55  /* D */,
  0x66  /* E */,
  0x0D  /* F */,
  0x15  /* 10 */,
  0x1D  /* 11 */,
  0x24  /* 12 */,
  0x2D  /* 13 */,
  0x2C  /* 14 */,
  0x35  /* 15 */,
  0x3C  /* 16 */,
  0x43  /* 17 */,
  0x44  /* 18 */,
  0x4D  /* 19 */,
  0x54  /* 1A */,
  0x5B  /* 1B */,
  0x5A  /* 1C */,
  0x14  /* 1D */,
  0x1C  /* 1E */,
  0x1B  /* 1F */,
  0x23  /* 20 */,
  0x2B  /* 21 */,
  0x34  /* 22 */,
  0x33  /* 23 */,
  0x3B  /* 24 */,
  0x42  /* 25 */,
  0x4B  /* 26 */,
  0x4C  /* 27 */,
  0x52  /* 28 */,
  0x0E  /* 29 */,
  0x12  /* 2A */,
  0x5D  /* 2B */,
  0x1A  /* 2C */,
  0x22  /* 2D */,
  0x21  /* 2E */,
  0x2A  /* 2F */,
  0x32  /* 30 */,
  0x31  /* 31 */,
  0x3A  /* 32 */,
  0x41  /* 33 */,
  0x49  /* 34 */,
  0x4A  /* 35 */,
  0x59  /* 36 */,
  0x00  /* 37 */,
  0x11  /* 38 */,
  0x29  /* 39 */,
  0x58  /* 3A */,
  0x5  /* 3B */,
  0x6  /* 3C */,
  0x4  /* 3D */,
  0x0C  /* 3E */,
  0x3  /* 3F */,
  0x0B  /* 40 */,
  0x83  /* 41 */,
  0x0A  /* 42 */,
  0x1  /* 43 */,
  0x9  /* 44 */,
  0x00  /* 45 */,
  0x00  /* 46 */,
  0x00  /* 47 */,
  0x00  /* 48 */,
  0x00  /* 49 */,
  0x7B  /* 4A */,
  0x00  /* 4B */,
  0x00  /* 4C */,
  0x00  /* 4D */,
  0x79  /* 4E */,
  0x00  /* 4F */,
  0x00  /* 50 */,
  0x00  /* 51 */,
  0x00  /* 52 */,
  0x00  /* 53 */,
  0x00  /* 54 */,
  0x00  /* 55 */,
  0x00  /* 56 */,
  0x00  /* 57 */,
  0x00  /* 58 */,
  0x00  /* 59 */,
  0x00  /* 5A */,
  0x00  /* 5B */,
  0x00  /* 5C */,
  0x00  /* 5D */,
  0x00  /* 5E */,
  0x00  /* 5F */,
  0x00  /* 60 */,
  0x00  /* 61 */,
  0x00  /* 62 */,
  0x00  /* 63 */,
  0x00  /* 64 */,
  0x7C  /* 65 */,
  0x7C  /* 66 */,
  0x6C  /* 67 */,
  0x75  /* 68 */,
  0x7D  /* 69 */,
  0x6B  /* 6A */,
  0x73  /* 6B */,
  0x74  /* 6C */,
  0x69  /* 6D */,
  0x72  /* 6E */,
  0x7A  /* 6F */,
  0x70  /* 70 */,
  0x71  /* 71 */,
  0x5A  /* 72 */
};

// ST to PS/2 keycode map
extern uint8_t stToPS2[] = {
  0x0  /* 0 */,
  0x1  /* 1 */,
  0x2  /* 2 */,
  0x3  /* 3 */,
  0x4  /* 4 */,
  0x5  /* 5 */,
  0x6  /* 6 */,
  0x7  /* 7 */,
  0x8  /* 8 */,
  0x9  /* 9 */,
  0xA  /* A */,
  0xB  /* B */,
  0xC  /* C */,
  0xD  /* D */,
  0xE  /* E */,
  0xF  /* F */,
  0x10  /* 10 */,
  0x11  /* 11 */,
  0x12  /* 12 */,
  0x13  /* 13 */,
  0x14  /* 14 */,
  0x15  /* 15 */,
  0x16  /* 16 */,
  0x17  /* 17 */,
  0x18  /* 18 */,
  0x19  /* 19 */,
  0x1A  /* 1A */,
  0x1B  /* 1B */,
  0x1C  /* 1C */,
  0x1D  /* 1D */,
  0x1E  /* 1E */,
  0x1F  /* 1F */,
  0x20  /* 20 */,
  0x21  /* 21 */,
  0x22  /* 22 */,
  0x23  /* 23 */,
  0x24  /* 24 */,
  0x25  /* 25 */,
  0x26  /* 26 */,
  0x27  /* 27 */,
  0x28  /* 28 */,
  0x29  /* 29 */,
  0x2A  /* 2A */,
  0x2B  /* 2B */,
  0x2C  /* 2C */,
  0x2D  /* 2D */,
  0x2E  /* 2E */,
  0x2F  /* 2F */,
  0x30  /* 30 */,
  0x31  /* 31 */,
  0x32  /* 32 */,
  0x33  /* 33 */,
  0x34  /* 34 */,
  0x35  /* 35 */,
  0x36  /* 36 */,
  0x0  /* 37 */,
  0x38  /* 38 */,
  0x39  /* 39 */,
  0x3A  /* 3A */,
  0x3B  /* 3B */,
  0x3C  /* 3C */,
  0x3D  /* 3D */,
  0x3E  /* 3E */,
  0x3F  /* 3F */,
  0x40  /* 40 */,
  0x41  /* 41 */,
  0x42  /* 42 */,
  0x43  /* 43 */,
  0x44  /* 44 */,
  0x0  /* 45 */,
  0x0  /* 46 */,
  0x0  /* 47 */,
  0x0  /* 48 */,
  0x0  /* 49 */,
  0x4A  /* 4A */,
  0x0  /* 4B */,
  0x0  /* 4C */,
  0x0  /* 4D */,
  0x4E  /* 4E */,
  0x0  /* 4F */,
  0x0  /* 50 */,
  0x0  /* 51 */,
  0x0  /* 52 */,
  0x0  /* 53 */,
  0x0  /* 54 */,
  0x0  /* 55 */,
  0x0  /* 56 */,
  0x0  /* 57 */,
  0x0  /* 58 */,
  0x0  /* 59 */,
  0x0  /* 5A */,
  0x0  /* 5B */,
  0x0  /* 5C */,
  0x0  /* 5D */,
  0x0  /* 5E */,
  0x0  /* 5F */,
  0x0  /* 60 */,
  0x0  /* 61 */,
  0x0  /* 62 */,
  0x0  /* 63 */,
  0x0  /* 64 */,
  0x37  /* 65 */,
  0x37  /* 66 */,
  0x47  /* 67 */,
  0x48  /* 68 */,
  0x49  /* 69 */,
  0x4B  /* 6A */,
  0x4C  /* 6B */,
  0x4D  /* 6C */,
  0x4F  /* 6D */,
  0x50  /* 6E */,
  0x51  /* 6F */,
  0x52  /* 70 */,
  0x53  /* 71 */,
  0x1C  /* 72 */
};

STKeyboard::STKeyboard(HardwareSerial* serial, int16_t pinLight, int16_t pinReset) {
    // save pins
    this->m_serial = serial;
    this->m_pinLight = pinLight;
    this->m_pinReset = pinReset;
}


void STKeyboard::initialize() {
    // set pins as OUTPUT
    pinMode(this->m_pinLight, OUTPUT);
    pinMode(this->m_pinReset, OUTPUT);
    digitalWrite(this->m_pinReset, HIGH);
    // turn off light
    this->setFloppyLight(false);
    // initialize the serial communication
    this->m_serial->begin(STKBD_baudrate);
    // reset stkbd
    delay(200);
    this->reset();
    delay(200);
}

int16_t STKeyboard::available() {
    return this->m_serial->available();
}

uint8_t STKeyboard::read() {
    return this->m_serial->read();
}

void STKeyboard::reset() {
    // bang RST pin
    digitalWrite(this->m_pinReset, HIGH);
    delay(20);
    digitalWrite(this->m_pinReset, LOW);
    delay(20);
    digitalWrite(this->m_pinReset, HIGH);
    // send command
    this->m_serial->write(0x80);
    this->m_serial->write(0x01);
    // remove all garbage data in serial
    delay(500);
    while(this->available()) this->read();
}

bool STKeyboard::getFloppyLight() { return m_lightState; }
void STKeyboard::setFloppyLight(bool value) {
    // save state
    m_lightState = value;
    // write to pin
    digitalWrite(this->m_pinLight, value ? LOW : HIGH);
}


bool STKeyboard::isMake(uint8_t code) { return !STKeyboard::isBreak(code); }
bool STKeyboard::isBreak(uint8_t code) { return !!(code & 0x80); }
uint8_t STKeyboard::getKey(uint8_t code) { return code & 0x7F; }
uint32_t STKeyboard::toPS2Keycode(uint8_t code, bool setone) {
  uint32_t res;
    uint8_t key = STKeyboard::getKey(code);
  // get actual key
  res |= setone ? stToPS2[key] : ps2set1to2[stToPS2[key]];
  // check if up, down, left, right arrow
  if (key == STKBD_KEY_UP ||
      key == STKBD_KEY_DOWN  ||
      key == STKBD_KEY_LEFT ||
      key == STKBD_KEY_RIGHT) {
    // check key
    uint8_t arrowkey = 0x75;
    switch(key) {
      case STKBD_KEY_UP: arrowkey = !setone ? 0x75 : 0x48; break;
      case STKBD_KEY_DOWN: arrowkey = !setone ? 0x72 : 0x50; break;
      case STKBD_KEY_LEFT: arrowkey = !setone ? 0x6B : 0x4B; break;
      case STKBD_KEY_RIGHT: arrowkey = !setone ? 0x74 : 0x4D; break;
    }
    // special code
    res |= (((uint32_t)0xE0) << (STKeyboard::isBreak(code) ? 16 : 8));
    res |= arrowkey;
  }
  // add break code
  if (STKeyboard::isBreak(code)) {
    res |= (((uint32_t)0xF0) << 8);
  }


  // return result
  return res;
}
