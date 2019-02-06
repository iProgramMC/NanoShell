# NanoShell for Arduino

WARNING: requires 1.5k of RAM, so be careful about which processor you put it on!
Technically, it should work on a MEGA 2560, but I haven't tried it yet.

Source and pictures can be found here and, hopefully, only here.

It uses Bodmer/TFT_ST7735 (and possibly adafruit/Adafruit-GFX-Library) libraries.
It also uses EEPROM.h and SPI.h.

# Connecting a few buttons
Make sure that the buttons are normally open and don't have latches.

UP -> Arduino pin 2
DOWN -> Arduino pin 3
LEFT -> Arduino pin 4
RIGHT -> Arduino pin 5
A Button -> Arduino pin 6
B Button -> Arduino pin 12

# Connecting the LCD
RST -> Arduino pin 7
CS -> Arduino pin 9
D/C -> Arduino pin 8
DIN -> Arduino pin 11
CLK -> Arduino pin 13

**WARNING**: Please change to these pins in the TFT library's "User_Setup.h" file or the gamepad/screen will **not** work!
