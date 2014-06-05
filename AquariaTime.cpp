/* 
 * File:   AquariaTime.cpp
 * Author: butchman
 * 
 * Created on June 1, 2014, 11:18 AM
 */

#include "AquariaTime.h"

// ---------------------Alarm functions -------------------//
// Turns the sunlight on

void SunlightOn() {
    digitalWrite(LIGHT_PIN_1, HIGH);
    digitalWrite(LIGHT_PIN_2, HIGH);
}
// Turns the sunlight off

void SunlightOff() {
    digitalWrite(LIGHT_PIN_1, LOW);
    digitalWrite(LIGHT_PIN_2, LOW);
}
// Turns the moonlight on

void MoonlightOn() {
    analogWrite(LIGHT_PIN_3, 25);
    analogWrite(LIGHT_PIN_4, 255);
    analogWrite(LIGHT_PIN_5, 25);
}
// Turns the moonlight off

void MoonlightOff() {
    analogWrite(LIGHT_PIN_3, 0);
    analogWrite(LIGHT_PIN_4, 0);
    analogWrite(LIGHT_PIN_5, 0);
}

void digitalClockDisplay() {
    Serial.print(hour());
    printDigits(minute());
    printDigits(second());
    Serial.print(" ");
    Serial.print(day());
    Serial.print(" ");
    Serial.print(month());
    Serial.print(" ");
    Serial.print(year());
    Serial.println();
}

void printDigits(int digits) {
    Serial.print(":");
    if (digits < 10)
        Serial.print('0');
    Serial.print(digits);
}

void printDigitsDate(int digits) {
    Serial.print("/");
    if (digits < 10)
        Serial.print('0');
    Serial.print(digits);
}


// Daylight check for initial startup

boolean isDaytimeNow(int dhr, int dmin, int dsec, int mhr, int mmin, int msec) {
    // startup lamp status checks
    time_t startOfDay = timeToSeconds(dhr, dmin, dsec); // Hour,Min,Secs for start of day;
    time_t startOfNight = timeToSeconds(mhr, mmin, msec); // Hour,Min,Secs for start of Night;

    // Change the current timestamp to secs
    time_t t = timeToSeconds(hour(), minute(), second());
    // If its between startOfDay & StartOfNight return true
    return (t >= startOfDay && t < startOfNight);
}

time_t timeToSeconds(time_t H, time_t M, time_t S) {
    return (H * SECS_PER_HOUR) + (M * SECS_PER_MIN) + S;
}

const char *monthName[12] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

tmElements_t tm;

bool getTime(const char *str) {
    int Hour, Min, Sec;

    if (sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec) != 3) return false;
    tm.Hour = Hour;
    tm.Minute = Min;
    tm.Second = Sec;
    return true;
}

bool getDate(const char *str) {
    char Month[12];
    int Day, Year;
    uint8_t monthIndex;

    if (sscanf(str, "%s %d %d", Month, &Day, &Year) != 3) return false;
    for (monthIndex = 0; monthIndex < 12; monthIndex++) {
        if (strcmp(Month, monthName[monthIndex]) == 0) break;
    }
    if (monthIndex >= 12) return false;
    tm.Day = Day;
    tm.Month = monthIndex + 1;
    tm.Year = CalendarYrToTm(Year);
    return true;
}

void setRTC() {

    // first check to see if the RTC is already set
    if (RTC.get == 0) {
        // it's not so initialize the RTC with info
        // from the compiler 
        getDate(__DATE__) && getTime(__TIME__);
        RTC.write(tm);
    }
    // it is so lets...
    setSyncProvider(RTC.get); // ...set the system time
    // and check to see if it worked
    if (timeStatus() != timeSet)
        Serial.println("Unable to sync with the RTC");
    else
        Serial.println("RTC has set the system time");
    setSyncInterval(60000); // sync system time with RTC every hour
}