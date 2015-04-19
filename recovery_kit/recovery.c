/*
 * Copyright (C) 2007 The Android Open Source Project
 * Copyright (C) 2010 NV
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <ctype.h>
#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/reboot.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#include "common.h"
#include "minui/minui.h"

#define RECOVERY_KIT_VERSION "1.30"

unsigned char stop_reboot = 0;

static void prompt_and_wait()
{
  char recovery[9];
  
  char* headers[] = { "recovery_kit v" RECOVERY_KIT_VERSION " by NV",
                      "(Based on Android system recovery utility)",
                      "",
                      "Use trackball to highlight;",
                      "click to select.",
                      "",
                      NULL };
  
  // these constants correspond to elements of the items[] list.
#define ITEM_REBOOT        0
#define ITEM_REBOOT_BOOT   1
#define ITEM_ENABLE_QXDM   2
#define ITEM_ADBD_RECOVERY 3
#define ITEM_RECOVERY      4
  char* items[] = { "Boot recovery partition [Home+Back]", 
                    "Boot boot partition [Home+Menu]", 
                    "Enable QXDM [Alt+Q]", 
                    "Start adbd recovery [Alt+A]", 
                    "Start recovery [Alt+R]", 
                    NULL };
  
  strcpy(recovery, "recovery");
  
  ui_start_menu(headers, items);
  int selected = 0;
  int chosen_item = -1;
  
  ui_reset_progress();
  for (;;) {
    int key = ui_wait_key();
    int alt = ui_key_pressed(KEY_LEFTALT) || ui_key_pressed(KEY_RIGHTALT);
    int visible = ui_text_visible();
    
    if (key == KEY_DREAM_BACK && ui_key_pressed(KEY_DREAM_HOME)) {
      // Wait for the keys to be released, to avoid triggering
      // special boot modes (like coming back into recovery!).
      while (ui_key_pressed(KEY_DREAM_BACK) ||
             ui_key_pressed(KEY_DREAM_HOME)) {
        usleep(1000);
      }
      chosen_item = ITEM_REBOOT;
      stop_reboot = 1;
    } else if (key == KEY_DREAM_MENU && ui_key_pressed(KEY_DREAM_HOME)) { 
     chosen_item = ITEM_REBOOT_BOOT;
      stop_reboot = 1;
    } else if (alt && key == KEY_Q) {
      chosen_item = ITEM_ENABLE_QXDM;
      stop_reboot = 1;
    } else if (alt && key == KEY_A) {
      chosen_item = ITEM_ADBD_RECOVERY;
      stop_reboot = 1;
    } else if (alt && key == KEY_R) {
      chosen_item = ITEM_RECOVERY;
      stop_reboot = 1;
    } else if ((key == KEY_DOWN || key == KEY_LEFT || key == KEY_VOLUMEDOWN) && visible) {
      ++selected;
      selected = ui_menu_select(selected);
      stop_reboot = 1;
    } else if ((key == KEY_UP || key == KEY_RIGHT || key == KEY_VOLUMEUP) && visible) {
      --selected;
      selected = ui_menu_select(selected);
      stop_reboot = 1;
    } else if (key == BTN_MOUSE && visible) {
      chosen_item = selected;
      stop_reboot = 1;
    }
    
    if (chosen_item >= 0) {
      // turn off the menu, letting ui_print() to scroll output
      // on the screen.
      ui_end_menu();

      switch (chosen_item) {
      case ITEM_REBOOT:
        ui_print("Rebooting(recovery)...\n");
        sync();
        __reboot(LINUX_REBOOT_MAGIC1, LINUX_REBOOT_MAGIC2, LINUX_REBOOT_CMD_RESTART2, recovery);
        return;
      case ITEM_REBOOT_BOOT:
        ui_print("Rebooting(boot)...\n");
        sync();
        reboot(RB_AUTOBOOT);
        return;
      case ITEM_ENABLE_QXDM:
        ui_print("\n-- Enabling QXDM...\n");
        system("echo 1 > /sys/devices/platform/msm_hsusb_periphera/qxdm_enable &");
        break;
      case ITEM_ADBD_RECOVERY:
        ui_print("\n-- Starting adbd recovery...\n");
        system("/sbin/adbd recovery &");
        break;
      case ITEM_RECOVERY:
        ui_print("\n-- Starting recovery...\n");
        system("/sbin/recovery &");
        return;
      }
      
      // if we didn't return from this function to reboot, show
      // the menu again.
      ui_start_menu(headers, items);
      selected = 0;
      chosen_item = -1;
      
      ui_reset_progress();
      
      // throw away keys pressed while the command was running,
      // so user doesn't accidentally trigger menu items.
      ui_clear_key_queue();
    }
  }
}

static void *reboot_thread(void *cookie)
{
  int i;
  char recovery[9];
  
  strcpy(recovery, "recovery");
  
  for (i = 0; i < 2; i++) {
    usleep(1000000);
  }
  
  if (!stop_reboot) {
    sync();
    __reboot(LINUX_REBOOT_MAGIC1, LINUX_REBOOT_MAGIC2, LINUX_REBOOT_CMD_RESTART2, recovery);
  }
  
  return NULL;
}

int main(int argc, char **argv)
{
  pthread_t t;
  
  // ui_init() が失敗しないように
  usleep(1500000);
  
  ui_init();
  
  pthread_create(&t, NULL, reboot_thread, NULL);
  
  prompt_and_wait();
  
  return EXIT_SUCCESS;
}
