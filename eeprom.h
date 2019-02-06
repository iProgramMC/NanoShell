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
