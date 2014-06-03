/* 
 * File:   AquariaLCD.cpp
 * Author: butchman
 * 
 * Created on June 3, 2014, 6:30 PM
 */

#include "AquariaLCD.h"

AquariaLCD::AquariaLCD() {
}

AquariaLCD::AquariaLCD(const AquariaLCD& orig) {
}

AquariaLCD::~AquariaLCD() {
}

int AquariaLCD::set_DisplayOn() {
    int rv = _command(0x41, 1);
    return rv;
}

int AquariaLCD::set_DisplayOff() {
    int rv = _command(0x42, 1);
    return rv;
}

int AquariaLCD::set_CursorPos(int pos) {

    Wire.beginTransmission(byte(address));
    Wire.write(0xFE);
    Wire.write(0x45);
    Wire.write(byte(pos));
    int rv = Wire.endTransmission();
    delay(1);
    return rv;
}

int AquariaLCD::set_CursorHome() {
    int rv = _command(0x46, 2);
    return rv;
}

int AquariaLCD::set_underlineOn() {
    int rv = _command(0x47, 2);
    return rv;
}

int AquariaLCD::set_underlineOff() {
    int rv = _command(0x48, 2);
    return rv;
}

int AquariaLCD::move_CursorL() {
    int rv = _command(0x49, 1);
    return rv;
}

int AquariaLCD::move_CursorR() {
    int rv = _command(0x4A, 1);
    return rv;
}

int AquariaLCD::set_BlinkingOn() {
    int rv = _command(0x4B, 1);
    return rv;
}

int AquariaLCD::set_BlinkingOff() {
    int rv = _command(0x4C, 1);
    return rv;
}

int AquariaLCD::backspace() {
    int rv = _command(0x4E, 1);
    return rv;
}

int AquariaLCD::clear_Screen() {
    int rv = _command(0x51, 2);
    return rv;
}

int AquariaLCD::set_Contrast() {
    Wire.beginTransmission(byte(address));
    Wire.write(0xFE);
    Wire.write(0x52);
    Wire.write(byte(contrast));
    int rv = Wire.endTransmission();
    delay(1);
    return rv;
}

int AquariaLCD::set_Brightness() {
    Wire.beginTransmission(byte(address));
    Wire.write(0xFE);
    Wire.write(0x53);
    Wire.write(byte(brightness));
    int rv = Wire.endTransmission();
    delay(1);
    return rv;
}

int AquariaLCD::shiftL() {
    int rv = _command(0x55, 1);
    return rv;
}

int AquariaLCD::shiftR() {
    int rv = _command(0x56, 1);
    return rv;
}

int AquariaLCD::show_Firmware() {
    int rv = _command(0x70, 5);
    return rv;
}

int AquariaLCD::show_Address() {
    int rv = _command(0x72, 5);
    return rv;
}

int AquariaLCD::display_char(int ch) {
    Wire.beginTransmission(byte(address));
    Wire.write(byte(ch));
    int rv = Wire.endTransmission();
    delay(5);
    return rv;
}

int AquariaLCD::display_string(char str[], int pos) {
    int rv = 0;
    int length = strlen(str);
    set_CursorPos(pos);
    for (int n = 0; n < length; ++n) {
        Wire.beginTransmission(byte(address));
        Wire.write(byte(str[n]));
        int rv = Wire.endTransmission();
        delay(1);
        if(rv != 0) {
            return rv;
        }
    };
    return rv;
}


// ----------------------------------------
// Private
// ----------------------------------------

int AquariaLCD::_command( int c, int d) {
    Wire.beginTransmission(byte(address));
    Wire.write(0xFE);
    Wire.write(byte(c));
    int rv = Wire.endTransmission();
    delay(d);
    return rv;
}
