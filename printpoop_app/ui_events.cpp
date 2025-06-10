#include <Arduino.h>
#include "ui.h"
#include "mqtt.h"
#include "accessory.h"

#include "song.h"
#include "nes_audio.h"



// App start here
void wait5second(lv_event_t* e) {
  lv_label_set_text(ui_status_label_wifisymbol, LV_SYMBOL_WIFI);
  lv_label_set_text(ui_intro_label_version, current_version.c_str());
  startMusicPlayback(start, 7);
  nonBlockDelaySec(5);
  _ui_screen_change(&ui_screen_status, LV_SCR_LOAD_ANIM_OVER_TOP, 500, 0, &ui_screen_status_screen_init);
  lv_anim_del(ui_intro_image_cap, (lv_anim_exec_xcb_t)_ui_anim_callback_set_image_angle);  //stop spinning

  wifimanager_init_reset(false);
  mqtt_init();
  initRTC();
}

// wifimanager web portal
void openSetupPortal(lv_event_t* e) {
  clickSound();
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("✅ Already connected to WiFi");
    Serial.println("ℹ️ Disconnecting and entering config mode...");
    // WiFi.disconnect(true);  // // Keep credentials
    // delay(1000);            // Let the WiFi stack settle
  }
  bool success = wm.startConfigPortal(AP_NAME);
  if (success) {
    Serial.println("✅ WiFi re-configured and connected");
  } else {
    Serial.println("⚠️ Config portal exited without WiFi connection");
    //  WiFi.begin();
  }
}


void closeSetupScreen(lv_event_t* e) {
  wm_configmode = false;  //let mqtt try connection
  clickSound();
}

static const uint8_t maxPage = 4;

void switch_previous_page(lv_event_t* e) {
  clickSound();
  pageIndex++;
  pageIndex = (pageIndex >= maxPage) ? 0 : pageIndex;
  page_control(pageIndex);
}

void switch_next_page(lv_event_t* e) {
  clickSound();
  pageIndex--;
  pageIndex = (pageIndex < 0) ? maxPage - 1 : pageIndex;
  page_control(pageIndex);
}

void closeSwingAnimation(lv_event_t* e) {  //stop swing animation
  clickSound();
  _ui_flag_modify(ui_status_image_swing, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
  _ui_flag_modify(ui_status_image_ppimage, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
  lv_anim_del(ui_status_image_swing, NULL);
  long_idle = false;
  idle_swing_now = false;
  print_started = false;
  print_swing_now = false;
   lv_img_set_angle(ui_status_image_swing, 0);//reset position
   lv_label_set_text(ui_status_label_ppmessage,"Meow! I am PrintpooP (Swipe left/right for pages)");
}
