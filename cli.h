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
  NanoShell CLI -> Command line (Just modded Notepad...)
  Copyright (c) iProgramInCpp 2019.
*/

#define CMD_BUF_SIZE 100
#define CMD_OUTPUT_SIZE 182

char* cmd_buf;

uint8_t TextPos = 0;

void draw_cli_window();
bool get_input_cli();
void draw_cli_text();

void cli_main() {
  if (!cmd_buf) {
    cmd_buf = malloc(CMD_BUF_SIZE);
  }
  memset(cmd_buf, 0, CMD_BUF_SIZE);
  draw_cli_window();
  draw_cli_text();
  draw_keyboard();
  draw_cursor();
  while (true) {
    if (!get_input_cli()) return;
  }
  free(cmd_buf);
  cmd_buf = NULL;
}


void draw_cli_text()
{
  uint8_t h;
  for (int i = 2; i < TextPos + 2; i++) {
    if (i % 26 == 0) {
      h += CHARACTER_GLCD_HEIGHT;
    }
  }
  tft.setCursor(0, tft.height() / 2 - 8 - h);
  tft.setTextColor(TFT_WHITE);
  tft.setTextWrap(true);
  tft.print("> ");
  for (int i = 0; i < TextPos; i++) {
    uint8_t ass = cmd_buf[i];
    tft.print((char)ass);
  }
  tft.print('_');
}

void draw_cli_window()
{
  tft.fillScreen(TFT_BLACK);
}

void process_cmd (char* cmd) {
  if (strcmp(cmd, "HELP") == 0) {
    tft.setCursor(0, 0);
    tft.setTextWrap(true);
    tft.setTextColor(TFT_WHITE);
    tft.print(F("Available commands: HELP, ECHO, TIME"));
  }
  if (strcmp(cmd, "HELP ECHO") == 0) {
    tft.setCursor(0, 0);
    tft.setTextWrap(true);
    tft.setTextColor(TFT_WHITE);
    tft.print(F("Returns what you type. For example: ECHO <message> outputs the message. Use this to check if the CLI works properly."));
  }
  if (strcmp(cmd, "HELP TIME") == 0) {
    tft.setCursor(0, 0);
    tft.setTextWrap(true);
    tft.setTextColor(TFT_WHITE);
    tft.print(F("Outputs the amount of time the shell has been running for."));
  }
  if (strcmp(cmd, "ECHO") == 0) {
    tft.setCursor(0, 0);
    tft.setTextWrap(true);
    tft.setTextColor(TFT_WHITE);
    strtok(cmd, ' ');
    tft.print(strtok(NULL, ' '));
  }
  if (strcmp(cmd, "TIME") == 0) {
    tft.setCursor(0, 0);
    tft.setTextWrap(true);
    tft.setTextColor(TFT_WHITE);
    tft.print(F("Sketch has been running for "));
    tft.print((float)(millis() / 1000));
    tft.print(F(" seconds."));
  }
}

bool get_input_cli()
{
  uint8_t flags = GetControllerState();
  if (flags & A_BUTTON && !(prevGPState & A_BUTTON)) {
    // Get Character
    uint8_t index = keyboardKeyY * 13 + keyboardKeyX;

    char character = keybChars[index];

    if (keyboardKeyY == 4) {
      // Function Keys.
      switch (keyboardKeyX) {
        case 0:
          // Tab key
          // Does nothing for now
          tft.fillRect(0, 0, tft.width(), tft.height() / 2, TFT_BLACK);
          break;
        case 1:
          // Space key
          tft.fillRect(0, 0, tft.width(), tft.height() / 2, TFT_BLACK);
          cmd_buf[TextPos] = ' ';
          TextPos++;
          break;
        case 2:
          // Backspace key
          tft.fillRect(0, 0, tft.width(), tft.height() / 2, TFT_BLACK);
          if (TextPos > 0) {
            cmd_buf[--TextPos] = ' ';
          }
          break;
        case 3:
          // Enter!
          tft.fillRect(0, 0, tft.width(), tft.height() / 2, TFT_BLACK);
          process_cmd(cmd_buf);
          memset(cmd_buf, 0, CMD_BUF_SIZE);
          TextPos = 0;
          break;
      }
      prevGPState = flags;
      draw_cli_text();
      draw_keyboard();
      draw_cursor();
    } else {
      cmd_buf[TextPos] = character;
      TextPos++;
      tft.fillRect(0, 0, tft.width(), tft.height() / 2, TFT_BLACK);
      prevGPState = flags;
      draw_cli_text();
      draw_keyboard();
      draw_cursor();
    }
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

    if (keyboardKeyY == 4 && keyboardKeyX > 3) keyboardKeyX = 3;
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
