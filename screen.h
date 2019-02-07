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
  NanoShell - SCREEN.H -> Screen functions.

  Copyright (c) iProgramInCpp 2019.
  Library (c) Adafruit Industries, Bodmer.
*/

#define APP_COUNT 6
#define APP_NOTEPAD 0
#define APP_CALCULATOR 1
#define APP_GPTEST 2
#define APP_DEMO 3
#define APP_CLI 5
#define APP_SETTINGS 4

#define CURAPP_DESKTOP 0
#define CURAPP_NOTEPAD 1
#define CURAPP_SETTINGS 2
#define CURAPP_CLI 3
#define CURAPP_CALCULATOR 4

#define CHARACTER_GLCD_WIDTH 6
#define CHARACTER_GLCD_HEIGHT 8

uint8_t CurrentApplication = CURAPP_DESKTOP;

#define DEFAULT_ROTATION 3

TFT_ST7735 tft = TFT_ST7735();       // Invoke custom library


float p = 3.1415926;

#define DLGTYPE_NONE -1
#define DLGTYPE_FORMAT 0
#define DLGTYPE_ABOUT 1

bool dlg_isShown = false;
bool dlg_responsePositive = false;
char* dlg_text1 = "";
char* dlg_text2 = "";
char* dlg_text3 = "";
char* dlg_caption = "";
char* dlg_option1 = "";
char* dlg_option2 = "";
int8_t dlg_type = DLGTYPE_NONE;
bool dlg_respPositivePicked = true;

uint8_t rotation = DEFAULT_ROTATION;

uint8_t SelectedApp = 0;

void MeasureString(char* text, uint8_t* x, uint8_t* y, uint8_t font = 0)
{
  uint8_t linew, h;
  uint8_t maxw;
  uint8_t lastw;
  uint16_t pos = 0;
  while (text[pos] != '\0') {
    switch (text[pos]) {
      case '\n':
        h += CHARACTER_GLCD_HEIGHT;
        lastw = linew;
        linew = 0;
        break;
      default:
        linew += CHARACTER_GLCD_WIDTH;
        maxw = max(lastw, linew);
        break;
    }
    pos++;
  }
  x = maxw;
  y = h;
}

void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void BSOD()
{
  tft.fillScreen(ST7735_BLUE);
  tft.setCursor(0, 0);
  tft.setTextWrap(true);
  tft.setTextColor(TFT_WHITE);
  tft.print(F("An error has occured, so Arduino has shut down to prevent further damage.\n\nIf this is the first time you're seeing this screen, press the RESET button on the Arduino. If not, reupload the sketch and look for bugs."));
}


void DrawDialog2()
{
  tft.setTextColor(dlg_respPositivePicked ? TFT_WHITE : TFT_BLACK);
  tft.setCursor(29, 81);
  tft.print(dlg_option1);
  tft.setTextColor(dlg_respPositivePicked ? TFT_BLACK : TFT_WHITE);
  tft.setCursor(93, 81);
  tft.print(dlg_option2);
}

void DrawDialog()
{
  tft.fillRect(4, 42, 156, 60, tft.color565(170, 170, 170));
  tft.fillRect(2, 40, 156, 60, tft.color565(210, 210, 210));
  tft.fillRect(2, 30, 156, 10, TFT_NAVY);
  tft.setTextColor(ST7735_WHITE);
  tft.setCursor(5, 32);
  tft.print(dlg_caption);
  tft.setTextColor(TFT_BLACK);
  tft.setCursor(5, 42);
  tft.print(dlg_text1);
  tft.setCursor(5, 50);
  tft.print(dlg_text2);
  tft.setCursor(5, 58);
  tft.print(dlg_text3);
  tft.drawLine(30, 80, 70, 80, TFT_WHITE);
  tft.drawLine(30, 80, 30, 90, TFT_WHITE);
  tft.drawLine(70, 80, 70, 90, TFT_BLACK);
  tft.drawLine(30, 90, 70, 90, TFT_BLACK);

  tft.drawLine(90, 80, 130, 80, TFT_WHITE);
  tft.drawLine(90, 80, 90, 90, TFT_WHITE);
  tft.drawLine(130, 80, 130, 90, TFT_BLACK);
  tft.drawLine(90, 90, 130, 90, TFT_BLACK);

  tft.setCursor(29, 81);
  tft.print(dlg_option1);
  tft.setCursor(93, 81);
  tft.print(dlg_option2);
}

void DrawText(uint8_t x, uint8_t y, uint16_t color, char* text)
{
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void ShowEEPROMFormatDlg()
{
  dlg_isShown = true;
  dlg_responsePositive = false;
  dlg_text1 = "Are you sure you want to ";
  dlg_text2 = "clear the EEPROM? You'll ";
  dlg_text3 = "lose all the data inside!";
  dlg_caption = "Clear the EEPROM?";
  dlg_option1 = "  Yes  ";
  dlg_option2 = "  No   ";
  dlg_type = DLGTYPE_FORMAT;
  DrawDialog();
}

void ShowAboutDlg()
{
  dlg_isShown = true;
  dlg_responsePositive = false;
  dlg_text1 = "NanoShell v0.01 alpha.   ";
  dlg_text2 = "(c) 2019 iProgramInCpp   ";
  dlg_text3 = "www.github.com/iProgramMC";
  dlg_caption = "About NanoShell";
  dlg_option1 = "  OK  ";
  dlg_option2 = "  OK  ";
  dlg_type = DLGTYPE_ABOUT;
  DrawDialog();
}

byte GetPixelFrom2BitImage(uint16_t* a, uint8_t x, uint8_t y)
{
  uint16_t b = a[y];
  return (b >> ((7 - x) * 2)) & 3;
}

#define PALETTE_CGA_CYAN 0
#define PALETTE_CGA_MAGENTA 1
#define PALETTE_CGA_RED 2
#define PALETTE_CGA_YELLOW 3
#define PALETTE_BLACKWHITE 4
#define PALETTE_EGA_BLUE 5
#define PALETTE_EGA_GREEN 6

#define BLOCK_CHARACTER 218


uint16_t ToTFTColor(byte c, byte palette)
{
  switch (palette) {
    case PALETTE_CGA_CYAN:
      switch (c) {
        case 0B00: return tft.color565(190, 190, 190);
        case 0B10: return TFT_WHITE;
        case 0B11: return TFT_BLACK;
        case 0B01: return TFT_CYAN;
      }
      break;
    case PALETTE_CGA_MAGENTA:
      switch (c) {
        case 0B00: return tft.color565(190, 190, 190);
        case 0B10: return TFT_WHITE;
        case 0B11: return TFT_BLACK;
        case 0B01: return TFT_MAGENTA;
      }
      break;
    case PALETTE_CGA_RED:
      switch (c) {
        case 0B00: return tft.color565(190, 190, 190);
        case 0B10: return TFT_WHITE;
        case 0B11: return TFT_BLACK;
        case 0B01: return TFT_RED;
      }
      break;
    case PALETTE_CGA_YELLOW:
      switch (c) {
        case 0B00: return tft.color565(190, 190, 190);
        case 0B10: return TFT_WHITE;
        case 0B11: return TFT_BLACK;
        case 0B01: return TFT_YELLOW;
      }
      break;
    case PALETTE_BLACKWHITE:
      switch (c) {
        case 0B00: return tft.color565(190, 190, 190);
        case 0B10: return TFT_WHITE;
        case 0B11: return TFT_BLACK;
        case 0B01: return tft.color565(128, 128, 128);
      }
      break;
    case PALETTE_EGA_BLUE:
      switch (c) {
        case 0B00: return tft.color565(190, 190, 190);
        case 0B10: return TFT_WHITE;
        case 0B11: return TFT_BLACK;
        case 0B01: return TFT_BLUE;
      }
      break;
    case PALETTE_EGA_GREEN:
      switch (c) {
        case 0B00: return tft.color565(190, 190, 190);
        case 0B10: return TFT_WHITE;
        case 0B11: return TFT_BLACK;
        case 0B01: return TFT_GREEN;
      }
      break;
  }
}

void DrawPixelScaled(int x, int y, uint16_t color, uint8_t scale) {
  for (int i = x; i < x + scale; i++) {
    tft.drawFastVLine(i, y, scale, color);
  }
}
void Draw2bitImage(uint16_t* a, uint8_t x, uint8_t y, uint8_t height, uint8_t palette, uint8_t width = 8)
{
  for (int i = y; i < y + height; i++) {
    for (int j = x; j < x + width; j++) {
      tft.drawPixel(j, i, ToTFTColor(GetPixelFrom2BitImage(a, j - x, i - y), palette));
    }
  }
}
void Draw2bitImageScaled(uint16_t* a, uint8_t x, uint8_t y, uint8_t height, uint8_t palette, uint8_t scale, uint8_t width = 8)
{
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      DrawPixelScaled(x + j * scale, y + i * scale, ToTFTColor(GetPixelFrom2BitImage(a, j, i), palette), scale);
    }
  }
}

void DrawDesktop()
{
  //tft.fillScreen(S7735_CYAN);
  testdrawtext("NanoShell Launcher v0.01", TFT_WHITE);
}
void DrawDesktopI()
{
  tft.fillScreen(tft.color565(190, 190, 190));
  tft.fillRect(0, 0, tft.width(), 10, TFT_NAVY);
  testdrawtext("NanoShell Launcher v0.01", TFT_WHITE);
  Draw2bitImage(notepad_half1_png, 5 + 5, 10, 16, PALETTE_CGA_CYAN);
  Draw2bitImage(notepad_half2_png, 13 + 5, 10, 16, PALETTE_CGA_CYAN);
  DrawText(24 + 5, 13, TFT_BLACK, "Notepad");
  Draw2bitImage(calculator_half1_png, 5 + 5, 28, 16, PALETTE_CGA_CYAN);
  Draw2bitImage(calculator_half2_png, 13 + 5, 28, 16, PALETTE_CGA_CYAN);
  DrawText(24 + 5, 31, TFT_BLACK, "Calculator");
  Draw2bitImage(controller_half1_png, 5 + 5, 46, 16, PALETTE_CGA_CYAN);
  Draw2bitImage(controller_half2_png, 13 + 5, 46, 16, PALETTE_CGA_CYAN);
  DrawText(24 + 5, 49, TFT_BLACK, "Gamepad Test");
  Draw2bitImage(a_png0, 5 + 5, 64, 16, PALETTE_EGA_BLUE);
  Draw2bitImage(a_png1, 13 + 5, 64, 16, PALETTE_EGA_BLUE);
  DrawText(24 + 5, 67, TFT_BLACK, "Demo");
  Draw2bitImage(settings_half1_png, 5 + 5, 82, 16, PALETTE_CGA_CYAN);
  Draw2bitImage(settings_half2_png, 13 + 5, 82, 16, PALETTE_CGA_CYAN);
  DrawText(24 + 5, 85, TFT_BLACK, "Settings");
  Draw2bitImage(cli_png0, 5 + 5, 100, 16, PALETTE_EGA_BLUE);
  Draw2bitImage(cli_png1, 13 + 5, 100, 16, PALETTE_EGA_BLUE);
  DrawText(24 + 5, 104, TFT_BLACK, "Command Line");
}
