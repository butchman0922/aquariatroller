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

boolean isDaytimeNow(int dhr,int dmin, int dsec, int mhr,int mmin, int msec) {
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
