/*
 * stkbd.h - a library to interface with an Atari ST keyboard.
 * Written by Ada Freeman (iLambda2), December 2017.
 * Release into public domain.
 */

#ifndef _STKBD_H
#define _STKBD_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <HardwareSerial.h>

// ATARI ST Rx/Tx baud rate
#define STKBD_baudrate  7812

// keycodes definitions
#define STKBD_KEY_ESC            0x01
#define STKBD_KEY_1              0x02
#define STKBD_KEY_2              0x03
#define STKBD_KEY_3              0x04
#define STKBD_KEY_4              0x05
#define STKBD_KEY_5              0x06
#define STKBD_KEY_6              0x07
#define STKBD_KEY_7              0x08
#define STKBD_KEY_8              0x09
#define STKBD_KEY_9              0x0A
#define STKBD_KEY_0              0x0B
#define STKBD_KEY_HYPHEN         0x0C
#define STKBD_KEY_EQUAL          0x0D
#define STKBD_KEY_BS             0x0E
#define STKBD_KEY_TAB            0x0F
#define STKBD_KEY_Q              0x10
#define STKBD_KEY_W              0x11
#define STKBD_KEY_E              0x12
#define STKBD_KEY_R              0x13
#define STKBD_KEY_T              0x14
#define STKBD_KEY_Y              0x15
#define STKBD_KEY_U              0x16
#define STKBD_KEY_I              0x17
#define STKBD_KEY_O              0x18
#define STKBD_KEY_P              0x19
#define STKBD_KEY_LEFTBRACE      0x1A
#define STKBD_KEY_RIGHTBRACE     0x1B
#define STKBD_KEY_RET            0x1C
#define STKBD_KEY_CTRL           0x1D
#define STKBD_KEY_A              0x1E
#define STKBD_KEY_S              0x1F
#define STKBD_KEY_D              0x20
#define STKBD_KEY_F              0x21
#define STKBD_KEY_G              0x22
#define STKBD_KEY_H              0x23
#define STKBD_KEY_J              0x24
#define STKBD_KEY_K              0x25
#define STKBD_KEY_L              0x26
#define STKBD_KEY_SEMICOLON      0x27
#define STKBD_KEY_APOSTROPHE     0x28
#define STKBD_KEY_BACKTICK       0x29
#define STKBD_KEY_LEFT_SHIFT     0x2A
#define STKBD_KEY_ANTISLASH      0x2B
#define STKBD_KEY_Z              0x2C
#define STKBD_KEY_X              0x2D
#define STKBD_KEY_C              0x2E
#define STKBD_KEY_V              0x2F
#define STKBD_KEY_B              0x30
#define STKBD_KEY_N              0x31
#define STKBD_KEY_M              0x32
#define STKBD_KEY_COMMA          0x33
#define STKBD_KEY_DOT            0x34
#define STKBD_KEY_SLASH          0x35
#define STKBD_KEY_RIGHT_SHIFT    0x36
#define STKBD_KEY_ALT            0x38
#define STKBD_KEY_SPACE_BAR      0x39
#define STKBD_KEY_CAPS_LOCK      0x3A
#define STKBD_KEY_F_1            0x3B
#define STKBD_KEY_F_2            0x3C
#define STKBD_KEY_F_3            0x3D
#define STKBD_KEY_F_4            0x3E
#define STKBD_KEY_F_5            0x3F
#define STKBD_KEY_F_6            0x40
#define STKBD_KEY_F_7            0x41
#define STKBD_KEY_F_8            0x42
#define STKBD_KEY_F_9            0x43
#define STKBD_KEY_F_10           0x44
#define STKBD_KEY_HOME           0x47
#define STKBD_KEY_UP                     0x48
#define STKBD_KEY_KEYPAD                 0x4A
#define STKBD_KEY_LEFT                   0x4B
#define STKBD_KEY_RIGHT                  0x4D
#define STKBD_KEY_KEYPAD                 0x4E
#define STKBD_KEY_DOWN                   0x50
#define STKBD_KEY_INSERT                 0x52
#define STKBD_KEY_DEL                    0x53
#define STKBD_KEY_ISO_KEY                0x60
#define STKBD_KEY_UNDO                   0x61
#define STKBD_KEY_HELP                   0x62
#define STKBD_KEY_KEYPAD_LEFTBRACKET     0x63
#define STKBD_KEY_KEYPAD_SLASH           0x64
#define STKBD_KEY_KEYPAD_ASTERISK        0x65
#define STKBD_KEY_KEYPAD_RIGHTBRACKET    0x66
#define STKBD_KEY_KEYPAD_7               0x67
#define STKBD_KEY_KEYPAD_8               0x68
#define STKBD_KEY_KEYPAD_9               0x69
#define STKBD_KEY_KEYPAD_4               0x6A
#define STKBD_KEY_KEYPAD_5               0x6B
#define STKBD_KEY_KEYPAD_6               0x6C
#define STKBD_KEY_KEYPAD_1               0x6D
#define STKBD_KEY_KEYPAD_2               0x6E
#define STKBD_KEY_KEYPAD_3               0x6F
#define STKBD_KEY_KEYPAD_0               0x70
#define STKBD_KEY_KEYPAD_DOT             0x71
#define STKBD_KEY_KEYPAD_ENTER           0x72

class STKeyboard {

    private:
        HardwareSerial* m_serial;
        int16_t m_pinLight;
        int16_t m_pinReset;
        bool m_lightState;

    public:
        STKeyboard(HardwareSerial* serial, int16_t pinLight, int16_t pinReset);

    public:
        void initialize();
        int16_t available();
        uint8_t read();
        void reset();

    public:
        bool getFloppyLight();
        void setFloppyLight(bool value);
        static bool isMake(uint8_t code);
        static bool isBreak(uint8_t code);
        static uint8_t getKey(uint8_t code);
        static uint32_t toPS2Keycode(uint8_t code);

    private:



};

#endif /* _STKBD_H */
