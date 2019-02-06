/*
  NanoShell Notepad -> Notepad on the go.
  Copyright (c) iProgramInCpp 2019.
*/

void draw_notepad_window();
void draw_keyboard();
bool get_input();
void draw_cursor();
void draw_text();

uint8_t keyboardKeyX = 0, keyboardKeyY = 0;
char* keybChars = "1234567890+=`QWERTYUIOP[].;ASDFGHJKL\"?(&ZXCVBNM!@#$)";

void notepad_main() {
  draw_notepad_window();
  loadEEPROM();
  draw_text();
  draw_keyboard();
  draw_cursor();
  while (true) {
    if (!get_input()) return;
  }
}

void draw_cursor()
{
  for (int i = 0; i < 13; i++) {
    for (int j = 0; j < 4; j++) {
      int xxxx = 5 + 12 * i, yyyy = tft.height() / 2 + 5 + j * 10;
      tft.drawRect(xxxx - 1, yyyy - 1, 8, 10, tft.color565(190, 190, 190));
    }
  }
  tft.drawRect(4, tft.height() / 2 + 44, 20, 10, tft.color565(190, 190, 190));
  tft.drawRect(29, tft.height() / 2 + 44, 66, 10, tft.color565(190, 190, 190));
  tft.drawRect(100, tft.height() / 2 + 44, 28, 10, tft.color565(190, 190, 190));
  tft.drawRect(130, tft.height() / 2 + 44, 28, 10, tft.color565(190, 190, 190));
  if (keyboardKeyY == 4) {
    switch (keyboardKeyX) {
      case 0:
        tft.drawRect(4, tft.height() / 2 + 44, 20, 10, TFT_BLACK);
        break;
      case 1:
        tft.drawRect(29, tft.height() / 2 + 44, 66, 10, TFT_BLACK);
        break;
      case 2:
        tft.drawRect(100, tft.height() / 2 + 44, 28, 10, TFT_BLACK);
        break;
      case 3:
        tft.drawRect(130, tft.height() / 2 + 44, 28, 10, TFT_BLACK);
        break;
    }
  } else {
    int xxxx2 = 5 + 12 * keyboardKeyX, yyyy2 = tft.height() / 2 + 5 + keyboardKeyY * 10;
    tft.drawRect(xxxx2 - 1, yyyy2 - 1, 8, 10, TFT_BLACK);
  }
}

void draw_text()
{
  uint8_t h;
  for (int i = 2; i < NotepadEEPROMAddr; i++) {
    switch (EEPROM[i]) {
      case '\n':
        h += CHARACTER_GLCD_HEIGHT;
        break;
      default:
        break;
    }
    if (i % 26 == 0) {
      h += CHARACTER_GLCD_HEIGHT;
    }
  }
  tft.setCursor(0, tft.height() / 2 - 8 - h);
  tft.setTextColor(TFT_BLACK);
  tft.setTextWrap(true);
  for (int i = 2; i < NotepadEEPROMAddr; i++) {
    uint8_t ass = EEPROM[i];
    tft.print((char)ass);
  }
  tft.print('_');
}

void draw_notepad_window()
{
  tft.fillScreen(TFT_WHITE);
  tft.fillRect(0, 0, tft.width(), 10, TFT_NAVY);
  tft.setCursor(1, 1);
  tft.setTextColor(TFT_WHITE);
  tft.print(F("NS Notepad // [B] - Exit"));
}

void draw_keyboard()
{
  tft.fillRect(0, tft.height() / 2, tft.width(), tft.height() / 2, tft.color565(190, 190, 190));
  tft.setCursor(5, tft.height() / 2 + 5);
  tft.setTextColor(TFT_BLACK);
  tft.print(F("1 2 3 4 5 6 7 8 9 0 + = `"));
  tft.setCursor(5, tft.height() / 2 + 5 + 10);
  tft.print(F("Q W E R T Y U I O P [ ] ."));
  tft.setCursor(5, tft.height() / 2 + 5 + 20);
  tft.print(F("; A S D F G H J K L \" ? ("));
  tft.setCursor(5, tft.height() / 2 + 5 + 30);
  tft.print(F("& Z X C V B N M ! @ # $ )"));
  tft.setCursor(5, tft.height() / 2 + 5 + 40);
  tft.print(F("TAB [         ] BKSP ENTR"));
}

bool get_input()
{
  uint8_t flags = GetControllerState();
  if (flags & A_BUTTON && !(prevGPState & A_BUTTON)) {
    // Write character
    EEPROM.put(0, NotepadEEPROMAddr);
    // Get Character
    uint8_t index = keyboardKeyY * 13 + keyboardKeyX;

    //char character = pgm_read_byte(keybChars + index);

    char character = keybChars[index];

    if (keyboardKeyY == 4) {
      // Function Keys.
      switch (keyboardKeyX) {
        case 0: EEPROM.write(NotepadEEPROMAddr, '\t'); NotepadEEPROMAddr += 1; break;
        case 1: EEPROM.write(NotepadEEPROMAddr, ' '); NotepadEEPROMAddr += 1; break;
        case 2:
          if (NotepadEEPROMAddr > 2) {
            NotepadEEPROMAddr -= 1;
            EEPROM.write(NotepadEEPROMAddr, ' ');
          }
          break;
        case 3: EEPROM.write(NotepadEEPROMAddr, '\n'); NotepadEEPROMAddr += 1; break;
      }
      tft.fillRect(0, 10, tft.width(), tft.height() / 2 - 10, TFT_WHITE);
      prevGPState = flags;
      draw_text();
      tft.fillRect(0, 0, tft.width(), 10, TFT_NAVY);
      tft.setCursor(1, 1);
      tft.setTextColor(TFT_WHITE);
      tft.print(F("NS Notepad // [B] - Exit"));
      draw_keyboard();
      draw_cursor();
    } else {
      EEPROM.write(NotepadEEPROMAddr, (byte)character);
      NotepadEEPROMAddr++;
      tft.fillRect(0, 10, tft.width(), tft.height() / 2 - 10, TFT_WHITE);
      draw_text();
      tft.fillRect(0, 0, tft.width(), 10, TFT_NAVY);
      tft.setCursor(1, 1);
      tft.setTextColor(TFT_WHITE);
      tft.print(F("NS Notepad // [B] - Exit"));
      draw_keyboard();
      draw_cursor();
      prevGPState = flags;
    }
    EEPROM.put(0, NotepadEEPROMAddr - 2);
    return true;
  }
  if (flags & B_BUTTON && !(prevGPState & B_BUTTON)) {
    return false;
  }

  if (flags & UP_BUTTON && !(prevGPState & UP_BUTTON)) {
    if (keyboardKeyY > 0) keyboardKeyY--;
    draw_cursor();
  }
  if (flags & DOWN_BUTTON && !(prevGPState & DOWN_BUTTON)) {
    if (keyboardKeyY < 4) keyboardKeyY++;

    if (keyboardKeyY == 4 && keyboardKeyX > 3
       ) keyboardKeyX = 3;
    draw_cursor();
  }
  if (flags & LEFT_BUTTON && !(prevGPState & LEFT_BUTTON)) {
    if (keyboardKeyX > 0) keyboardKeyX--;
    draw_cursor();
  }
  if (flags & RIGHT_BUTTON && !(prevGPState & RIGHT_BUTTON)) {
    if (keyboardKeyY == 4) {
      if (keyboardKeyX < 3) keyboardKeyX++;
    } else {
      if (keyboardKeyX < 12) keyboardKeyX++;
    }
    draw_cursor();
  }

  prevGPState = flags;

  return true;
}
