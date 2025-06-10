#pragma once

#include <Arduino.h>
/*
struct mytime {
  uint8_t h, m, s;
}; 
extern mytime currentTime;
*/

extern bool print_started;
extern bool print_swing_now;
extern String TZoffset;  // timezone offset
extern String current_version;
extern bool firmware_checked;
extern String firmware_manifest;
extern bool mpu_install;

void initRTC();
String get_current_time();
/*------------ SOUND EFFECT ----------*/
 void initSpeaker();
 void beepbeep();
 void beep();
 void clickSound();
 /*-----------------------------*/
void autoDim();
void init_TFT_BL(uint8_t BL_PIN);
 /*-----------------------------*/
void setVersion(const String ver, String manifest);
bool newFirmwareAvailable();
/*-----------------------------*/
void mpu_init(byte sda,byte scl);
void print_animation();