# Instructions on  how to compile the source code.

Requirement:

 * Hardware: CYD 2.4" ESP32 Dev Board
 * IDE: Arduino IDE 2.3.6
 * ESP32 Core: 2.0.7
 * Board: ESP32 Dev Module
 * Partition scheme: Huge App 3MB/SPIFF 1MB
   

Library:
- TFT_eSPI / lvgl / etc.. as needed by the sketch

------------
Update the TFT_eSPI library.

1. Copy "User_Setup_Select.h" into the sketch folder "c:/arduino/Sketch/libraries/TFT_eSPI"
 
* Please backup an old "User_Setup_Select.h" file
  
2. Copy "User_Setups/Setup_CYD_2_4.h" and "User_Setups/Setup_CYD_2_8.h" into folder "TFT_eSPI/User_Setups"
------------
To select the board type to compile

## 2.4" screen 

Edit "User_Setup_Select.h"

#include <User_Setups/Setup_CYD_2_4.h>

//#include <User_Setups/Setup_CYD_2_8.h>

in the file "printpoop_app.ino" line no. 25 -> //#define USE_TFT_28

## 2.8" screen

Edit "User_Setup_Select.h"

//#include <User_Setups/Setup_CYD_2_4.h>

#include <User_Setups/Setup_CYD_2_8.h>

in the file "printpoop_app.ino" line no. 25 -> #define USE_TFT_28

------------


