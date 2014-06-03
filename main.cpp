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