#include <Arduino.h>
#include "AquariaLCD.h"
#include "AquariaTime.h"

// Initalize our objects
extern HardwareSerial Serial;

void print2digits(int number) {
    if (number >= 0 && number < 10) {
        Serial.write('0');
    }
    Serial.print(number);
}

void setup() {

    // Start communication Interfaces
    Serial.begin(9600);
    Wire.begin();

    char logo[] = "Aquariatroller";
    char menu1[] = "Setup";

    // Initialize the LCD
    AquariaLCD lcd;
    lcd.address = 40;
    lcd.contrast = 45;
    lcd.brightness = 6;

    lcd.set_DisplayOn();
    lcd.clear_Screen();
    lcd.set_Contrast();
    lcd.set_Brightness();
    lcd.clear_Screen();
    lcd.display_string(logo, 0x00);
    lcd.display_string(menu1, 0x40);

    // Initialize the RTC
    setAquariaTime();

    // Set our alarms
    Alarm.alarmRepeat(8, 30, 0, SunlightOn); // 8:30am every day
    Alarm.alarmRepeat(21, 00, 0, SunlightOff); // 9:00pm every day 
    Alarm.alarmRepeat(21, 01, 0, MoonlightOn); // 9:01pm every day
    Alarm.alarmRepeat(8, 29, 0, MoonlightOff); // 8:29am every day

    // Daylight check and initialize lamps
    if (isDaytimeNow(8, 30, 0, 21, 01, 0)) {
        MoonlightOff();
        SunlightOn();
    } else {
        SunlightOff();
        MoonlightOn();
    }
}

time_t prevDisplay = 0; // when the digital clock was displayed

void loop() {
    //update the display only if time has changed
    if (now() != prevDisplay) {
        prevDisplay = now();
        digitalClockDisplay();
    }
    // check alarms every minute
    Alarm.delay(60000);
}