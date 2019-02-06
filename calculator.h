/*
  NanoShell - AVRDEFF.H -> AVR Default Functions (Setup() and Loop())

  Copyright (c) iProgramInCpp 2019.
  Library (c) Adafruit Industries, Bodmer.
*/

#define CALCBUF_LEN 16
char* calcopbuf;
char* calcopbuf2;
uint8_t calcbufpos = 0;

uint8_t keyboard_height;
uint8_t key_width, key_height;
uint8_t keypadKeyX, keypadKeyY;

char* calckeys = "C0=+123-456*789/";

void calculate()
{
  // Dupe the buffer
  memcpy(calcopbuf2, calcopbuf, CALCBUF_LEN);

  // The two numbers
  int32_t a = 0;
  int32_t b = 0;
  // Result
  int32_t r = 0;

  // Used to get operand 2
  char* d = NULL;

  // List of valid operators - used for STRTOK.
  char* e = "+-/*";

  // Operator
  char h = 0;

  // Get both operators...
  strtok(calcopbuf2, e);
  d = strtok(NULL, e);

  // ... and the operator.
  h = calcopbuf[strlen(calcopbuf2)];

  // Now get the int32s from them.
  a = atoi(calcopbuf2);
  b = atoi(d);

  // Free the D buffer after that.
  free(d);

  // Now do the math...
  switch (h) {
    case '+': r = a + b; break;
    case '-': r = a - b; break;
    case '*': r = a * b; break;
    case '/':
      // Check if dividing by zero.
      if (b != 0) {
        tft.fillRect(0, 18, tft.width(), 8, TFT_WHITE);
        tft.setCursor(0, 18);
        tft.setTextColor(TFT_BLACK);
        tft.print((float)a / (float)b);
        return;
      }
      // and print the message if we do.
      tft.fillRect(0, 18, tft.width(), 8, TFT_WHITE);
      tft.setCursor(0, 18);
      tft.setTextColor(TFT_BLACK);
      tft.print(F("Cannot divide by zero"));
      return;
  }

  // ... and print the result (when not dividing, we want a special print when we do)
  tft.fillRect(0, 18, tft.width(), 8, TFT_WHITE);
  tft.setCursor(0, 18);
  tft.setTextColor(TFT_BLACK);
  tft.print(r);
  return;
}

void draw_cursor_calc()
{
  for (int i = 0; i < 4; i++) {
    for (int j = 1; j < 5; j++) {
      tft.drawRect(i * key_width, tft.height() - j * key_height, key_width, key_height, TFT_WHITE);
    }
  }
  tft.drawRect(keypadKeyX * key_width, tft.height() - (keypadKeyY + 1) * key_height, key_width, key_height, TFT_BLACK);
}

bool get_input_calc()
{
  uint8_t flags = GetControllerState();

  if (flags & B_BUTTON) {
    prevGPState = flags;
    return false;
  }

  if (flags & A_BUTTON && !(prevGPState & A_BUTTON)) {
    if (keypadKeyX == 2 && keypadKeyY == 0) {
      // equals
      calculate();
      memset(calcopbuf, 0, CALCBUF_LEN);
      tft.fillRect(0, 10, tft.width(), 8, TFT_WHITE);
      tft.setCursor(0, 10);
      tft.setTextColor(TFT_BLACK);
      tft.setTextWrap(true);
      tft.print(calcopbuf);
      calcbufpos = 0;
    } else if (keypadKeyX == 0 && keypadKeyY == 0) {
      // clear
      if (calcbufpos > 0) {
        calcopbuf[--calcbufpos] = 0;
        tft.fillRect(0, 10, tft.width(), 8, TFT_WHITE);
        tft.setCursor(0, 10);
        tft.setTextColor(TFT_BLACK);
        tft.setTextWrap(true);
        tft.print(calcopbuf);
      }
    } else {
      tft.fillRect(0, 10, tft.width(), 8, TFT_WHITE);
      char aa = calckeys[keypadKeyY * 4 + keypadKeyX];
      calcopbuf[calcbufpos++] = aa;
      tft.setCursor(0, 10);
      tft.setTextColor(TFT_BLACK);
      tft.setTextWrap(true);
      tft.print(calcopbuf);
    }
    delay(1000);
  }

  if (flags & UP_BUTTON && !(prevGPState & UP_BUTTON)) {
    if (keypadKeyY < 3) ++keypadKeyY;
    draw_cursor_calc();
  }
  if (flags & DOWN_BUTTON && !(prevGPState & DOWN_BUTTON)) {
    if (keypadKeyY > 0) --keypadKeyY;
    draw_cursor_calc();
  }
  if (flags & LEFT_BUTTON && !(prevGPState & LEFT_BUTTON)) {
    if (keypadKeyX > 0) --keypadKeyX;
    draw_cursor_calc();
  }
  if (flags & RIGHT_BUTTON && !(prevGPState & RIGHT_BUTTON)) {
    if (keypadKeyX < 3) ++keypadKeyX;
    draw_cursor_calc();
  }

  prevGPState = flags;
  return true;
}

void draw_calc_window()
{
  tft.fillScreen(TFT_WHITE);
  tft.fillRect(0, 0, tft.width(), 10, TFT_NAVY);
  tft.setCursor(2, 2);
  tft.setTextColor(TFT_WHITE);
  tft.print(F("NS Calculator // B - Exit"));
  tft.setTextSize(1);

  keyboard_height = tft.height();

  // Determine optimal size
  // by reserving four character spaces.
  keyboard_height -= CHARACTER_GLCD_HEIGHT * 4;

  // .. and the title bar
  keyboard_height -= 10;

  // Now determine the key width/height

  key_width = tft.width() / 4;
  key_height = keyboard_height / 4;

  for (int i = 0; i < 4; i++) {
    for (int j = 1; j < 5; j++) {
      uint8_t key_center_x, key_center_y;
      key_center_x = i * key_width + key_width / 2;
      key_center_y = tft.height() - j * key_height + key_height / 2;
      tft.fillRect(i * key_width, tft.height() - j * key_height, key_width, key_height, TFT_BLACK);
      tft.drawRect(i * key_width, tft.height() - j * key_height, key_width, key_height, TFT_WHITE);

      tft.setCursor(key_center_x - 6, key_center_y - 8);
      tft.setTextSize(2);
      tft.print(calckeys[(j - 1) * 4 + i]);

      // tft.fillRect(1 + j * 32, tft.height - (i + 1) * 32 - 1, 30, 30, TFT_BLACK);
    }
  }
  tft.setTextSize(1);
}

void calculator_main()
{
  if (!calcopbuf) {
    calcopbuf = malloc(CALCBUF_LEN);
  }
  if (!calcopbuf2) {
    calcopbuf2 = malloc(CALCBUF_LEN);
  }
  memset(calcopbuf, 0, CALCBUF_LEN);
  memset(calcopbuf2, 0, CALCBUF_LEN);
  draw_calc_window();
  draw_cursor_calc();
  while (true) {
    if (!get_input_calc()) return;
  }
}
