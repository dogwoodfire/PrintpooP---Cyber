## WORK BOTH 2.4" and 2.8" Resistive Touch Screen
## Source code uploaded
## Firmware version: 1.3.0 (display on the top left-most on the welcome screen)
Important Notice:

Heads up! This firmware is still a work in progress
It's not officially released yet, so things might break or not work as expected.
We’re working hard to get it ready — thanks for your understanding!
- [Flash Firmware Online for 2.4" and 2.8"](https://vaandcob.github.io/webpage/src/index.html)
- Develop progress [ 25% ]
  
[Youtube](https://youtu.be/cmsc_lcnK_s)

![PrintpooP](/picture/animation.gif)

## PrintpooP – Retro Pixel Smart Display for Bambu Lab A1

Introduction   This doesn’t make my prints any better… but it does make my printer look way cooler 😂

A compact, ESP32-powered accessory designed specifically for the Bambu Lab A1, A1 Mini 3D printer. It replaces the original hotend faceplate with a custom 3D-printed enclosure (the "Box") that houses a vibrant 2.4" touchscreen display.

📡 Live Status Display
PrintpooP connects to your A1 via Wi-Fi and presents real-time print data, such as print progress, temperatures, fan speeds, and Clock. Right at the print head. This localised status view makes monitoring more intuitive and visually engaging.

🎮 8-Bit Aesthetic
All visuals are styled in charming 8-bit pixel art, giving your printer a retro personality. Animations and icons are custom-designed to blend nostalgic design with functional UX.

🧠 Powered by ESP32
At its core is a single integrated module combining the ESP32 SoC with the 2.4" TFT, delivering reliable connectivity and rendering performance without external components.

🛠️ Easy Mounting
The enclosure is engineered to replace the Bambu Lab A1's default hotend faceplate, securing PrintpooP in a clean, integrated form factor.


HOW TO USE: 
1. Touch screen calibration will be shown at the first run, but can be manually entered by pressing the RESET button and then pressing BOOT (GPIO_0) button within a second and hold
2. Follow the screen instructions. (Click the SETUP button on the screen to enter network configuration)
3. Access the setup web portal by connecting to the SSID PirntpooP_Setup using a smartphone or laptop.
4. Configure Wi-Fi credentials on the Configure Wi-Fi page.
5. Enter the printer's IP address, access code, serial number, and time zone on the SETUP page.
   
    How to get printer serial number:  https://wiki.bambulab.com/en/general/find-sn
   
    How to get printer IP address & Access Code:  https://wiki.bambulab.com/en/software/bambu-studio/failed-to-send-print-files
6. Currently, there are 3 status display pages
   
    Page 1 - Temperature / Fan
   
    Page 2 - Print progress
   
    Page 3 - AMS filament type and colour

![Screen](/picture/screen1.jpg)
![Network Setup](/picture/screen2.jpg)

---------------------------------------------------------------------------------------------------

## Part list:

- [3D Print part at MakerWorld](https://makerworld.com/en/models/1432974-PrintpooP-faceplate-kit#profileId-1490390)
- [ESP32 2.4" 240 x 320 Resistive Touch Display](s.click.aliexpress.com/e/_omgP1zh)
- [1W 8R 2809 Loud speaker 8 ohms 1 Watt 8R 1W 28*9*3.6MM](s.click.aliexpress.com/e/_oDSKVf9)

## [☕ Buy me coffee](https://buymeacoffee.com/vaandcob)
