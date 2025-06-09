# Compiling the Source Code for PrintPooP Project

This guide provides instructions on how to set up your environment and compile the source code for the PrintPooP project.

## 1. Prerequisites & Setup

Ensure your environment matches the following requirements:

* **Hardware:** CYD 2.4" ESP32 Dev Board (or compatible 2.8" version, see specific setup below)
* **IDE:** Arduino IDE 2.3.6 (or compatible)
* **ESP32 Core:** Version 2.0.7 (or compatible)
* **Board Selection in IDE:** "ESP32 Dev Module"
* **Partition Scheme:** "Max App Only (3.9MB App)"
    * **Action:** You must add this custom partition scheme to your Arduino IDE *before* compiling. Instructions for this are located in the `/addon/partitions` folder of this project.
    https://github.com/VaAndCob/PrintpooP/tree/main/printpoop_app/addon/partitions

* **Required Libraries:**
    * `TFT_eSPI`
    * `lvgl`
    * *(And any other libraries specified as needed by the sketch)*
    * **Action:** Ensure all necessary libraries are installed in your Arduino IDE.

---

## 2. Configure the `TFT_eSPI` Library

These steps configure the `TFT_eSPI` library specifically for the CYD display.

**A. Backup Existing `User_Setup_Select.h` (Important!)**

   Before proceeding, it's highly recommended to back up your current `User_Setup_Select.h` file if you use `TFT_eSPI` for other projects.
   * Locate the file, typically at: `C:\Users\{YourUsername}\Documents\Arduino\libraries\TFT_eSPI\User_Setup_Select.h` (Windows) or `~/Documents/Arduino/libraries/TFT_eSPI/User_Setup_Select.h` (macOS/Linux). The exact path might vary based on your sketchbook location.

**B. Copy Provided `TFT_eSPI` Configuration Files:**

1.  **Copy `User_Setup_Select.h`:**
    * Copy the `User_Setup_Select.h` file provided with *this project* into your `TFT_eSPI` library folder, overwriting the existing one.
    * Example path: `C:\Users\{YourUsername}\Documents\Arduino\libraries\TFT_eSPI\`

2.  **Copy `User_Setups` Files:**
    * Copy the `Setup_CYD_2_4.h` and `Setup_CYD_2_8.h` files (provided with *this project* in a `User_Setups` folder or similar) into the `User_Setups` subfolder within your `TFT_eSPI` library.
    * Example path: `C:\Users\{YourUsername}\Documents\Arduino\libraries\TFT_eSPI\User_Setups\`

---

## 3. Select Target Screen Size for Compilation

You need to configure the project for either a 2.4" or 2.8" screen by editing two files: `User_Setup_Select.h` (within the `TFT_eSPI` library folder) and `printpoop_app.ino` (your main sketch file).

### For a 2.4" Screen

1.  **Edit `User_Setup_Select.h`** (in your `TFT_eSPI` library folder):
    * Ensure the following lines are set:
        ```cpp
        #include <User_Setups/Setup_CYD_2_4.h> // Active
        //#include <User_Setups/Setup_CYD_2_8.h> // Commented out
        ```

2.  **Edit `printpoop_app.ino`** (your main sketch file):
    * Go to approximately line 28 and make sure the `USE_TFT_28` macro is commented out:
        ```cpp
        // #define USE_TFT_28 // Should be commented out for 2.4" screen
        ```

### For a 2.8" Screen

1.  **Edit `User_Setup_Select.h`** (in your `TFT_eSPI` library folder):
    * Ensure the following lines are set:
        ```cpp
        //#include <User_Setups/Setup_CYD_2_4.h> // Commented out
        #include <User_Setups/Setup_CYD_2_8.h> // Active
        ```

2.  **Edit `printpoop_app.ino`** (your main sketch file):
    * Go to line 28 and make sure the `USE_TFT_28` macro is defined (uncommented):
        ```cpp
        #define USE_TFT_28 // Should be active for 2.8" screen
        ```

---

## 4. Compile and Upload

After completing the above steps:

1.  Open the `printpoop_app.ino` sketch in your Arduino IDE.
2.  Ensure the correct Board ("ESP32 Dev Module") and Partition Scheme ("Max App Only (3.9MB App)") are selected under the `Tools` menu.
3.  Compile and upload the sketch to your ESP32 CYD board.

---
