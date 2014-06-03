#include <Arduino.h>
#include "AquariaLCD.h"
#include "AquariaTime.h"

// Initalize our objects
extern HardwareSerial Serial;

void setup() {

    // Start Serial Interface
    Serial.begin(9600);
    // Make sure the system time and the RTC are in sync
    setSyncProvider(RTC.get); // set the system time
    if (timeStatus() != timeSet)
        Serial.println("Unable to sync with the RTC");
    else
        Serial.println("RTC has set the system time");
    setSyncInterval(60000); // sync system time with RTC every hour

    // Set our alarms
    Alarm.alarmRepeat(8, 30, 0, SunlightOn); // 8:30am every day
    Alarm.alarmRepeat(21, 00, 0, SunlightOff); // 9:00pm every day 
    Alarm.alarmRepeat(21, 01, 0, MoonlightOn); // 9:01pm every day
    Alarm.alarmRepeat(8, 29, 0, MoonlightOff); // 8:29am every day

    // Daylight check and initialize lamps
    if (isDaytimeNow(8, 30, 0, 21, 00, 0)) {
        MoonlightOff();
        SunlightOn();
    } else {
        SunlightOff();
        MoonlightOn();
    }

    char logo[] = "Aquariatroller";
    char menu1[] = "Setup";


    AquariaLCD lcd;
    lcd.address = 40;
    lcd.contrast = 45;
    lcd.brightness = 6;

    Wire.begin();
    lcd.set_DisplayOn();
    lcd.set_Contrast();
    lcd.set_Brightness();
    lcd.clear_Screen();
    lcd.display_string(logo, 0x00);
    lcd.display_string(menu1, 0x40);

}

time_t prevDisplay = 0; // when the digital clock was displayed

void loop() {

    //update the display only if time has changed
    if (now() != prevDisplay) {
        prevDisplay = now();
        digitalClockDisplay();
    }

    // check alarms
    Alarm.delay(1000);
}