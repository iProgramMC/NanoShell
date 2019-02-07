/*
MIT License

Copyright (c) 2019 iProgramInCpp

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/
/*
  NanoShell - AVRDEFF.H -> AVR Default Functions (Setup() and Loop())

  Copyright (c) iProgramInCpp 2019.
  Library (c) Adafruit Industries, Bodmer.
*/

bool hasTriggeredEasterEgg = 0;

void setup(void)
{
  /* Initialize devices such as SD-card, Screen, Serial port and GamePad. */

  Serial.begin(230400);
  Serial.println(F("ArduinOS v0.1 alpha. (c) iProgramInCpp 2019."));
  InitializeGamepad();
  // UP = 2, DOWN = 3, LEFT = 4, RIGHT = 5, ACCEPT = 6, DENY = 10


  uint8_t flags;
  flags = GetControllerState();
  if (flags & A_BUTTON) {
    hasTriggeredEasterEgg = true;
  }

  // Use this initializer if you're using a 1.8" TFT
  tft.init();   // initialize a ST7735S chip
  tft.fillScreen(ST7735_BLACK);
  Serial.println(F("Screen has initialized."));
  tft.setRotation(DEFAULT_ROTATION);

  tft.fillRect(4, 42, 156, 60, tft.color565(10, 10, 10));
  tft.fillRect(2, 40, 156, 60, tft.color565(210, 210, 210));
  tft.fillRect(2, 30, 156, 10, TFT_NAVY);

  tft.setTextColor(ST7735_WHITE);
  tft.setCursor(5, 32);
  tft.print(F("Please wait..."));
  tft.setTextColor(TFT_BLACK);
  tft.setCursor(5, 70);

  Draw2bitImageScaled(a_png0, 2, 40, 16, PALETTE_EGA_BLUE, 2, 8);
  Draw2bitImageScaled(a_png1, 18, 40, 16, PALETTE_EGA_BLUE, 2, 8);
  Draw2bitImageScaled(a_png2, 34, 40, 16, PALETTE_EGA_BLUE, 2, 8);
  Draw2bitImageScaled(a_png3, 50, 40, 16, PALETTE_EGA_BLUE, 2, 8);
  Draw2bitImageScaled(a_png4, 66, 40, 16, PALETTE_EGA_BLUE, 2, 8);
  Draw2bitImageScaled(a_png5, 82, 40, 16, PALETTE_EGA_BLUE, 2, 8);
  Draw2bitImageScaled(a_png6, 98, 40, 16, PALETTE_EGA_BLUE, 2, 8);
  Draw2bitImageScaled(a_png7, 114, 40, 16, PALETTE_EGA_BLUE, 2, 8);
  Draw2bitImageScaled(a_png8, 130, 40, 16, PALETTE_EGA_BLUE, 2, 8);
  Draw2bitImageScaled(a_png9, 146, 40, 16, PALETTE_EGA_BLUE, 2, 6);

  tft.print(F("\n NanoComp is starting up."));
  
  DrawDesktopI();

}

void loop() {
  uint8_t flags;
  flags = GetControllerState();


  DrawDesktop();

  if (dlg_isShown) {
    DrawDialog2();
  }


  if (flags & A_BUTTON && !(prevGPState & A_BUTTON)) {
    // A-Button
    if (dlg_isShown) {
      dlg_responsePositive = dlg_respPositivePicked;
      dlg_isShown = false;
      DrawDesktopI();
      if (dlg_responsePositive) {
        ExecuteDialogAction();
      }
      dlg_type = DLGTYPE_NONE;
    } else {
      switch (SelectedApp) {
        case APP_NOTEPAD:
          prevGPState = flags;
          Notepad_Start();
          DrawDesktopI();
          break;
        case APP_CALCULATOR:
          prevGPState = flags;
          Calculator_Start();
          DrawDesktopI();
          break;
        case APP_GPTEST:
          GamePadTest_Start();
          break;
        case APP_DEMO:
          prevGPState = flags;
          DemoApp_Start();
          DrawDesktopI();
          break;
        case APP_CLI:
          prevGPState = flags;
          CLI_Start();
          DrawDesktopI();
          break;
        case APP_SETTINGS:
          //        rotation = (rotation + 1) % 4;
          //        tft.setRotation(rotation);
          //        DrawDesktopI();
          prevGPState = flags;
          Settings_Start();
          DrawDesktopI();
          break;
      }
    }
  }
  if (flags & B_BUTTON) {
    // B-Button
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
    if (SelectedApp > 0) {
      SelectedApp--;
    }
  }
  if (flags & DOWN_BUTTON && !(prevGPState & DOWN_BUTTON)) {
    // Down
    if (SelectedApp < APP_COUNT - 1) {
      SelectedApp++;
    }
  }

  if (!dlg_isShown) {
    for (int i = 0; i < APP_COUNT; i++) {
      if (i != SelectedApp) {
        tft.fillRect(2, 16 + i * 18, 6, 5, tft.color565(190, 190, 190));
      }
    }
    Draw2bitImage(select_arrow, 2, 16 + SelectedApp * 18, 5, PALETTE_CGA_CYAN);
  }

  //for (int i = 7; 0 <= i; i--) {
  //  Serial.print((flags & (1 << i)) ? '1' : '0');
  //}
  prevGPState = flags;
}
