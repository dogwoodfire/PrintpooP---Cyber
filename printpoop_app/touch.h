#include <XPT2046_Touchscreen.h>
#include <Preferences.h>
Preferences prefCal;

SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen ts(TOUCH_CS, TOUCH_IRQ);  //pin config in Setup_CYD_2_x.h

// Initialise with example calibration values so processor does not crash if setTouch() not called in setup()
uint16_t touchCalibration_x0 = 300, touchCalibration_x1 = 3600, touchCalibration_y0 = 300, touchCalibration_y1 = 3600;
uint8_t touchCalibration_rotate = 1, touchCalibration_invert_x = 2, touchCalibration_invert_y = 0;
long _pressTime;

//------------------------------------------------------------------------------------------
//load calibration data
void setTouch(uint16_t *parameters) {
  touchCalibration_x0 = parameters[0];
  touchCalibration_x1 = parameters[1];
  touchCalibration_y0 = parameters[2];
  touchCalibration_y1 = parameters[3];

  if (touchCalibration_x0 == 0) touchCalibration_x0 = 1;
  if (touchCalibration_x1 == 0) touchCalibration_x1 = 1;
  if (touchCalibration_y0 == 0) touchCalibration_y0 = 1;
  if (touchCalibration_y1 == 0) touchCalibration_y1 = 1;

  touchCalibration_rotate = parameters[4] & 0x01;
  touchCalibration_invert_x = parameters[4] & 0x02;
  touchCalibration_invert_y = parameters[4] & 0x04;
}
//-------------------------------------
//calibrate touch screen within windows 0,0,320,240
void calibrateTouch(uint16_t *parameters, uint32_t color_fg, uint32_t color_bg, uint8_t size) {
  int16_t values[] = { 0, 0, 0, 0, 0, 0, 0, 0 };

  for (uint8_t i = 0; i < 4; i++) {
    tft.fillRect(0, 0, size + 1, size + 1, color_bg);
    tft.fillRect(0, TFT_HEIGHT - size - 1, size + 1, size + 1, color_bg);
    tft.fillRect(TFT_WIDTH - size - 1, 0, size + 1, size + 1, color_bg);
    tft.fillRect(TFT_WIDTH - size - 1, TFT_HEIGHT - size - 1, size + 1, size + 1, color_bg);

    if (i == 5) break;  // used to clear the arrows

    switch (i) {
      case 0:  // up left
        tft.drawLine(0, 0, 0, size, color_fg);
        tft.drawLine(0, 0, size, 0, color_fg);
        tft.drawLine(0, 0, size, size, color_fg);
        break;
      case 1:  // bot left
        tft.drawLine(0, TFT_HEIGHT - size - 1, 0, TFT_HEIGHT - 1, color_fg);
        tft.drawLine(0, TFT_HEIGHT - 1, size, TFT_HEIGHT - 1, color_fg);
        tft.drawLine(size, TFT_HEIGHT - size - 1, 0, TFT_HEIGHT - 1, color_fg);
        break;
      case 2:  // up right
        tft.drawLine(TFT_WIDTH - size - 1, 0, TFT_WIDTH - 1, 0, color_fg);
        tft.drawLine(TFT_WIDTH - size - 1, size, TFT_WIDTH - 1, 0, color_fg);
        tft.drawLine(TFT_WIDTH - 1, size, TFT_WIDTH - 1, 0, color_fg);
        break;
      case 3:  // bot right
        tft.drawLine(TFT_WIDTH - size - 1, TFT_HEIGHT - size - 1, TFT_WIDTH - 1, TFT_HEIGHT - 1, color_fg);
        tft.drawLine(TFT_WIDTH - 1, TFT_HEIGHT - 1 - size, TFT_WIDTH - 1, TFT_HEIGHT - 1, color_fg);
        tft.drawLine(TFT_WIDTH - 1 - size, TFT_HEIGHT - 1, TFT_WIDTH - 1, TFT_HEIGHT - 1, color_fg);
        break;
    }

    // user has to get the chance to release
    if (i > 0) delay(1000);

    for (uint8_t j = 0; j < 8; j++) {
      // Use a lower detect threshold as corners tend to be less sensitive
      while (!ts.touched())
        ;

      TS_Point p = ts.getPoint();
      values[i * 2] += p.x;
      values[i * 2 + 1] += p.y;
    }
    values[i * 2] /= 8;
    values[i * 2 + 1] /= 8;
    clickSound();
  }

  // from case 0 to case 1, the y value changed.
  // If the measured delta of the touch x axis is bigger than the delta of the y axis, the touch and TFT axes are switched.
  touchCalibration_rotate = false;
  if (abs(values[0] - values[2]) > abs(values[1] - values[3])) {
    touchCalibration_rotate = true;
    touchCalibration_x0 = (values[1] + values[3]) / 2;  // calc min x
    touchCalibration_x1 = (values[5] + values[7]) / 2;  // calc max x
    touchCalibration_y0 = (values[0] + values[4]) / 2;  // calc min y
    touchCalibration_y1 = (values[2] + values[6]) / 2;  // calc max y
  } else {
    touchCalibration_x0 = (values[0] + values[2]) / 2;  // calc min x
    touchCalibration_x1 = (values[4] + values[6]) / 2;  // calc max x
    touchCalibration_y0 = (values[1] + values[5]) / 2;  // calc min y
    touchCalibration_y1 = (values[3] + values[7]) / 2;  // calc max y
  }

  // in addition, the touch screen axis could be in the opposite direction of the TFT axis
  touchCalibration_invert_x = false;
  if (touchCalibration_x0 > touchCalibration_x1) {
    values[0] = touchCalibration_x0;
    touchCalibration_x0 = touchCalibration_x1;
    touchCalibration_x1 = values[0];
    touchCalibration_invert_x = true;
  }
  touchCalibration_invert_y = false;
  if (touchCalibration_y0 > touchCalibration_y1) {
    values[0] = touchCalibration_y0;
    touchCalibration_y0 = touchCalibration_y1;
    touchCalibration_y1 = values[0];
    touchCalibration_invert_y = true;
  }

  // pre calculate
  touchCalibration_x1 -= touchCalibration_x0;
  touchCalibration_y1 -= touchCalibration_y0;

  if (touchCalibration_x0 == 0) touchCalibration_x0 = 1;
  if (touchCalibration_x1 == 0) touchCalibration_x1 = 1;
  if (touchCalibration_y0 == 0) touchCalibration_y0 = 1;
  if (touchCalibration_y1 == 0) touchCalibration_y1 = 1;

  // export parameters, if pointer valid
  if (parameters != NULL) {
    parameters[0] = touchCalibration_x0;
    parameters[1] = touchCalibration_x1;
    parameters[2] = touchCalibration_y0;
    parameters[3] = touchCalibration_y1;
    parameters[4] = touchCalibration_rotate | (touchCalibration_invert_x << 1) | (touchCalibration_invert_y << 2);
    /*
    Serial.println("x0 = " + String(touchCalibration_x0));
    Serial.println("x1 = " + String(touchCalibration_x1));
    Serial.println("y0 = " + String(touchCalibration_y0));
    Serial.println("y1 = " + String(touchCalibration_y1));
    */
  }
}
//-------------------------------------
void touch_calibrate() {
  uint16_t calData[5];
  bool calDataOK = false;

  // Check if the calibration data key exists
  prefCal.begin("TouchCal", false);

  if (prefCal.isKey("calData")) {
    size_t bytesRead = prefCal.getBytes("calData", calData, sizeof(calData));
    if (bytesRead == sizeof(calData)) {
      calDataOK = true;
      Serial.println(F("Calibration data loaded successfully from Preferences"));
    } else {
      Serial.println(F("Calibration data in Preferences is corrupt (incorrect size)"));
      // Optionally remove the bad key
      prefCal.remove("calData");
    }
  } else {
    Serial.println(F("No calibration data found in Preferences"));
  }
  prefCal.end();

  // If we have valid calibration data AND button is not pressed
  if (calDataOK && (digitalRead(SELECTOR_PIN) == HIGH)) {
    Serial.println(F("Using stored calibration data"));
    setTouch(calData);  // Apply calibration data
  } else {
    // Need to calibrate - either no valid data or button pressed
    if (!calDataOK) {
      Serial.println(F("No valid calibration data - starting calibration"));
    } else {
      Serial.println(F("Button pressed - forcing recalibration"));
      beep();
    }

    // Run the calibration procedure

    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_BLACK, TFT_CYAN);
    tft.drawCentreString("Touch screen", TFT_WIDTH / 2, TFT_HEIGHT / 2 - 10, 4);
    tft.drawCentreString("calibration", TFT_WIDTH / 2, TFT_HEIGHT / 2 + 16, 4);
    tft.setCursor(40, 0);
    tft.setTextFont(2);
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.println(F("Touch corners as indicated"));
    tft.setTextFont(1);
    tft.println();

    // Run the actual calibration
    calibrateTouch(calData, TFT_YELLOW, TFT_BLACK, 20);

    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.println(F("Calibration complete!"));

    // The putBytes function will create the key if it doesn't exist, or update it if it does.
    prefCal.begin("TouchCal", false);
    size_t bytesWritten = prefCal.putBytes("calData", calData, sizeof(calData));

    if (bytesWritten == sizeof(calData)) {
      Serial.println(F("Calibration data saved to Preferences successfully"));

      // Optional: Verification by reading back (though putBytes is generally reliable)
      uint16_t verifyData[5];
      size_t verifyBytesRead = prefCal.getBytes("calData", verifyData, sizeof(verifyData));
      if (verifyBytesRead == sizeof(verifyData) && memcmp(calData, verifyData, sizeof(calData)) == 0) {
        Serial.println(F("Calibration data in Preferences verified successfully"));
      } else {
        Serial.println(F("Calibration data verification in Preferences failed"));
      }
      
    } else {
      Serial.println(F("Failed to save calibration data to Preferences"));
    }
    prefCal.end();
  }
}


//--------------------------
//get touch point
bool getTouch(uint16_t *x, uint16_t *y) {
 // int threshold;

  if (ts.touched()) {
    TS_Point p = ts.getPoint();
    uint16_t x_tmp = p.x, y_tmp = p.y, xx, yy;

  //  if (_pressTime > millis()) threshold = 20;
    uint8_t n = 5;
    uint8_t valid = 0;
    while (n--) {
      if (ts.touched()) valid++;
      ;
    }
    if (valid < 1) {
      _pressTime = 0;
      return false;
    }
    _pressTime = millis() + 50;

    //compensate
    if (!touchCalibration_rotate) {
      xx = (x_tmp - touchCalibration_x0) * TFT_WIDTH / touchCalibration_x1;
      yy = (y_tmp - touchCalibration_y0) * TFT_HEIGHT / touchCalibration_y1;
      if (touchCalibration_invert_x)
        xx = TFT_WIDTH - xx;
      if (touchCalibration_invert_y)
        yy = TFT_HEIGHT - yy;
    } else {
      xx = (y_tmp - touchCalibration_x0) * TFT_WIDTH / touchCalibration_x1;
      yy = (x_tmp - touchCalibration_y0) * TFT_HEIGHT / touchCalibration_y1;
      if (touchCalibration_invert_x)
        xx = TFT_WIDTH - xx;
      if (touchCalibration_invert_y)
        yy = TFT_HEIGHT - yy;
    }

    if (xx >= TFT_WIDTH || yy >= TFT_HEIGHT) return false;  //out of window
    *x = xx;
    *y = yy;
    return true;
  } else {
    return false;
  }
}
//--------------------------
void testTouch() {            //for test touch screen
  uint16_t t_x = 0, t_y = 0;  // To store the touch coordinates
  tft.fillScreen(TFT_BLACK);
  while (true) {
    if (getTouch(&t_x, &t_y)) {
      Serial.printf("%d , %d\n", t_x, t_y);
      tft.drawPixel(t_x, t_y, TFT_WHITE);
      delay(300);
    }
  }
}