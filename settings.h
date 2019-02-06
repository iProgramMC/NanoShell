/*
  NanoShell Settings
  Copyright (c) iProgramInCpp 2019.
*/

#define SETTING_ROTATE 0
#define SETTING_CLEARROM 1
#define SETTING_RESET 2
#define SETTING_ABOUT 3
#define SETTING_EXIT 4

#define SETTING_COUNT 5

uint8_t SelectedItemSettings = SETTING_ROTATE;

void DrawSettings()
{
  //tft.fillScreen(S7735_CYAN);
  testdrawtext("NanoShell Settings", TFT_WHITE);
}
void DrawSettingsUI()
{
  tft.fillScreen(tft.color565(190, 190, 190));
  tft.fillRect(0, 0, tft.width(), 10, TFT_NAVY);
  testdrawtext("NanoShell Settings", TFT_WHITE);
  Draw2bitImage(rotate_png0, 5 + 5, 10, 16, PALETTE_CGA_CYAN);
  Draw2bitImage(rotate_png1, 13 + 5, 10, 16, PALETTE_CGA_CYAN);
  DrawText(24 + 5, 13, TFT_BLACK, "Rotate Screen");
  Draw2bitImage(cleareeprom_png0, 5 + 5, 28, 16, PALETTE_CGA_CYAN);
  Draw2bitImage(cleareeprom_png1, 13 + 5, 28, 16, PALETTE_CGA_CYAN);
  DrawText(24 + 5, 31, TFT_BLACK, "Clear EEPROM");
  Draw2bitImage(reset_png0, 5 + 5, 46, 16, PALETTE_CGA_RED);
  Draw2bitImage(reset_png1, 13 + 5, 46, 16, PALETTE_CGA_RED);
  DrawText(24 + 5, 49, TFT_BLACK, "Reboot");
  Draw2bitImage(info_png0, 5 + 5, 64, 16, PALETTE_EGA_BLUE);
  Draw2bitImage(info_png1, 13 + 5, 64, 16, PALETTE_EGA_BLUE);
  DrawText(24 + 5, 67, TFT_BLACK, "About NanoShell");
  Draw2bitImage(exit_png0, 5 + 5, 82, 16, PALETTE_CGA_RED);
  Draw2bitImage(exit_png1, 13 + 5, 82, 16, PALETTE_CGA_RED);
  DrawText(24 + 5, 85, TFT_BLACK, "Exit");
}

void Settings_Start()
{
  //  tft.fillScreen(TFT_BLACK);
  //  tft.setCursor(1, 1);
  //  tft.setTextColor(TFT_WHITE);
  //  tft.println(F("Dumping EEPROM over Serial. Please set your baud rate to 230400 baud."));
  //  DumpEEPROM();
  //  tft.println(F("Press B to exit."));
  //  uint8_t flags = 0;
  //  while(!((flags = GetControllerState()) & B_BUTTON));

  CurrentApplication = CURAPP_SETTINGS;

  DrawSettingsUI();
  while (true) {
    DrawSettings();
    if (dlg_isShown) {
      DrawDialog2();
    }
    uint8_t flags = GetControllerState();

    if (flags & A_BUTTON && !(prevGPState & A_BUTTON)) {
      // A-Button
      if (dlg_isShown) {
        dlg_responsePositive = dlg_respPositivePicked;
        dlg_isShown = false;
        DrawSettingsUI();
        if (dlg_responsePositive) {
          ExecuteDialogAction();
        }
        dlg_type = DLGTYPE_NONE;
      } else {
        switch (SelectedItemSettings) {
          case SETTING_ROTATE:
            rotation = (rotation + 1) % 4;
            tft.setRotation(rotation);
            DrawSettingsUI();
            break;
          case SETTING_CLEARROM:
            ShowEEPROMFormatDlg();
            break;
          case SETTING_RESET:
            reset_system();
            break;
          case SETTING_ABOUT:
            ShowAboutDlg();
            break;
          case SETTING_EXIT:
            CurrentApplication = CURAPP_DESKTOP;
            return;
            break;
        }
      }
    }
    if (flags & LEFT_BUTTON) {
      // Left
      if (dlg_isShown) {
        dlg_respPositivePicked = true;
      }
    }
    if (flags & RIGHT_BUTTON) {
      // Right
      if (dlg_isShown) {
        dlg_respPositivePicked = false;
      }
    }

    if (flags & UP_BUTTON && !(prevGPState & UP_BUTTON)) {
      // Up
      if (SelectedItemSettings > 0) {
        SelectedItemSettings--;
      }
    }
    if (flags & DOWN_BUTTON && !(prevGPState & DOWN_BUTTON)) {
      // Down
      if (SelectedItemSettings < SETTING_COUNT - 1) {
        SelectedItemSettings++;
      }
    }

    if (!dlg_isShown) {
      for (int i = 0; i < SETTING_COUNT; i++) {
        if (i != SelectedItemSettings) {
          tft.fillRect(2, 16 + i * 18, 6, 5, tft.color565(190, 190, 190));
        }
      }
      Draw2bitImage(select_arrow, 2, 16 + SelectedItemSettings * 18, 5, PALETTE_CGA_CYAN);
    }
    prevGPState = flags;
  }
}
