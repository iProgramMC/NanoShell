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
  NanoShell - EEPROM.H -> Built-in functions for EEPROM
  (basically completes the EEPROM.h library)

  Copyright (c) iProgramInCpp 2019.
  Library (c) Adafruit Industries, Bodmer.
*/

uint16_t NotepadEEPROMAddr = 0;

void ClearEEPROM()
{
  uint16_t ll = EEPROM.length();
  for (uint16_t i = 0; i < ll; i++) {
    EEPROM.update(i, 0);
  }

}

void loadEEPROM()
{
  uint16_t length = 2;
  EEPROM.get(0, length);
  NotepadEEPROMAddr = length + 2;
}

void DumpEEPROM()
{
  Serial.print("0: ");
  for (int i = 0; i < EEPROM.length(); i++) {
    if (i % 16 == 0 && i != 0) {
      Serial.println();
      Serial.print(i, HEX);
      Serial.print(": ");
    }
    Serial.print(EEPROM[i], HEX);
    Serial.print(' ');
  }

  for (int i = 0; i < EEPROM.length(); i++) {
    Serial.write(EEPROM[i]);
  }
}
