# arduino-stkeyboard
An arduino library to interface with an atari 520/1040ST keyboard.

## api

The following methods are available:

### constructor
```cpp
STKeyboard(HardwareSerial* serial, int16_t pinLight, int16_t pinReset);
```
Create a STKeyboard object.
* **serial** : the serial port used to connect the keyboard.
* **pinLight** : the pin connected to the floppy light (active LOW).
* **pinReset** : the pin connected to the keyboard reset control (active LOW).

### initialize
```cpp
void initialize();
```
Initialize the STKeyboard object. This method must be called at least once before you start using the keyboard.

### available
```cpp
int16_t available();
```
Returns the number of bytes that are available to be read from the keyboard.

*NB : in use, similar to Serial.available()*

### read
```cpp
uint8_t read();
```
Read the last byte of data available from the keyboard.

*NB : in use, similar to Serial.read()*

### reset
```cpp
void reset();
```
Send a pulse unto the RESET pin of the keyboard and relaunch the initialization procedure (0x80 then 0x01).

### get/setFloppyLight
```cpp
bool getFloppyLight();
void setFloppyLight(bool state);
```
Returns the state of the floppy light, or change its state.

*NB : the STKeyboard class has an internal buffer to keep track of the state of the floppy light. Do NOT use digitalWrite(FLOPPYLIGHT_PIN, value) if you want getFloppyLight() to return accurate data.*

### isMake
```cpp
static bool isMake(uint8_t stcode);
```
Returns true iff the keycode (Atari ST type) is a make code. (<=> code & 0x80 == 0)

### isBreak
```cpp
static bool isBreak(uint8_t stcode);
```
Returns true iff the keycode (Atari ST type) is a break code. (<=> code & 0x80 != 0)

### getKey
```cpp
static uint8_t getKey(uint8_t stcode);
```
Returns the key represented by the code : that is, the make code for the given key (<=> code & 0x7F)

### toPS2Keycode
```cpp
static uint32_t toPS2Keycode(uint8_t stcode);
```
Returns the corresponding PS2 keycode, given an Atari ST code.
The data can be send to thee PS/2 port with the following procedure :
```cpp
uint32_t ps2code = STKeyboard::toPS2Keycode(stcode)
// get bytes
uint8_t lo = ps2code & 0xFF;
uint8_t mi = ps2code & 0xFF00;
uint8_t hi = ps2code & 0xFF0000;
// send lo bytes
if (hi && mi && lo) { write(hi); }
if (mi && lo)       { write(mi); }
if (lo)             { write(lo); } else { return -1 }
```
