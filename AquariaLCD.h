/* 
 * File:   AquariaLCD.h
 * Author: butchman
 *
 * Created on June 3, 2014, 6:30 PM
 */

#ifndef AQUARIALCD_H
#define	AQUARIALCD_H

#include <Arduino.h>
#include <Wire.h>

class AquariaLCD {

public:

    int address; // device address
    int contrast; // 1 - 50 
    int brightness; // 1 - 8

    AquariaLCD();
    AquariaLCD(const AquariaLCD& orig);
    virtual ~AquariaLCD();

    /*
     * This command displays a single character at the current cursor position.  
     */
    int display_char(int ch);
    
    /*
     * This command displays a string at the pos cursor position.  
     */
    int display_string(char str[], int pos);

    /*
     * This command moves the cursor position right 1 space whether the cursor is turned on or 
     * not. The displayed character is not altered.
     */
    int move_CursorR();

    /*
     * This command moves the cursor position left 1 space whether the cursor is turned on or 
     * not. The displayed character is not altered.
     */
    int move_CursorL();

    /*
     * This  command  is  destructive  backspace.  The  cursor  is  moved  back  one  space  and  the 
     * character on the cursor is deleted.  
     */
    int backspace();

    /*
     * This command shifts the display to the left 1 space. The cursor position also moves with 
     * the display, and the display data is not altered
     */
    int shiftL();

    /*
     * This command shifts the display to the right 1 space. The cursor position also moves with 
     * the display, and the display data is not altered
     */
    int shiftR();


    /*
     * This command sets the display contrast. The contrast setting can be between 1 and 50, 
     * where 50 is the highest contrast. 
     */
    int set_Contrast();

    /*
     * This command sets the backlight brightness level. The value can be between 1 and 8. 
     * Default:  8 
     */
    int set_Brightness();

    /*
     * This command turns on the LCD display screen. The display text is not altered. 
     */
    int set_DisplayOn();

    /*
     * This command turns off the LCD display screen. The display text is not altered. 
     */
    int set_DisplayOff();

    /*
     * This command moves the cursor to a specified location where the next character will be 
     * displayed.  The typical cursor position for a 2‐line 16‐character display is show below; a 
     * cursor position outside these ranges will not be viewable. 
     *  
     *        Column 1    Column 16 
     * Line 1  0x00        0x0F 
     * Line 2  0x40        0x4F 
     *
     * Default:  After a reset, the cursor is on position 0x00
     */
    int set_CursorPos(int pos);

    /*
     * This command moves the cursor to line 1, column 1 of the LCD screen. The display text is 
     * not altered.
     */
    int set_CursorHome();

    /*
     * This command turns on the blinking cursor.  
     */
    int set_BlinkingOn();

    /*
     * This command turns off the blinking cursor.  
     */
    int set_BlinkingOff();

    /*
     * This command turns on the underline cursor. 
     */
    int set_underlineOn();

    /*
     * This command turns off the underline cursor. 
     */
    int set_underlineOff();


    /*
     * This command clears the entire display and place the cursor at line 1 column 1. 
     */
    int clear_Screen();

    /*
     * This command displays the current I 2 C slave address. 
     */
    int show_Address();

    /*
     * This command displays the firmware version. 
     */
    int show_Firmware();

private:

    /*
     * Returns
     * byte, which indicates the status of the transmission:
     * 
     * 0:success
     * 1:data too long to fit in transmit buffer
     * 2:received NACK on transmit of address
     * 3:received NACK on transmit of data
     * 4:other error 
     */
    int _command(int com, int del);

};

#endif	/* AQUARIALCD_H */

