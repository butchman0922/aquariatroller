/* 
 * File:   AquariaTime.h
 * Author: butchman
 *
 * Created on June 1, 2014, 11:18 AM
 */

#ifndef AQUARIATIME_H
#define	AQUARIATIME_H

// needed to build from netbeans
#include <Arduino.h>
extern HardwareSerial Serial;

// includes for timer functions
#include <Time.h>
#include <TimeAlarms.h>
#include <Wire.h>
#include <DS1307RTC.h>

// Begin user configuration ------------------------ //

// Setup our pins
// Sunlight
#define LIGHT_PIN_1 6
#define LIGHT_PIN_2 7
// Moonlight
#define LIGHT_PIN_3 3 // Red
#define LIGHT_PIN_4 9 // Blue
#define LIGHT_PIN_5 5 // Green


// End user configuration -------------------------- //

// Alarms for lighting control
void SunlightOn();
void SunlightOff();
void MoonlightOn();
void MoonlightOff();

// Functions for initalizing our lighting
boolean isDaytimeNow(int dhr, int dmin, int dsec, int mhr, int mmin, int msec);
time_t timeToSeconds(time_t H, time_t M, time_t S);

//  Serial Clock Display functions
void digitalClockDisplay(); // digital clock display of the time
void printDigits(int digits); // utility for digital clock display: prints preceding colon and leading 0
void printDigitsDate(int digits); // utility function for digital clock display: prints preceding ":" and leading 0

void setRTC();

#endif	/* AQUARIATIME_H */

