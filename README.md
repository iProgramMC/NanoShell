# NanoShell for Arduino

WARNING: requires 1.5k of RAM, so be careful about which processor you put it on!
Technically, it should work on a MEGA 2560, but I haven't tried it yet.

Source and pictures can be found here and, hopefully, only here.

It uses Bodmer/TFT_ST7735 (and possibly adafruit/Adafruit-GFX-Library) libraries.
It also uses EEPROM.h and SPI.h.

# Connecting a few buttons
Make sure that the buttons are normally open and don't have latches.

* UP -> Arduino pin 2, 
* DOWN -> Arduino pin 3, 
* LEFT -> Arduino pin 4, 
* RIGHT -> Arduino pin 5, 
* A Button -> Arduino pin 6, 
* B Button -> Arduino pin 12.

# Connecting the LCD
* RST -> Arduino pin 7, 
* CS -> Arduino pin 9, 
* D/C -> Arduino pin 8, 
* DIN -> Arduino pin 11, 
* CLK -> Arduino pin 13, 

**WARNING**: Please change to these pins in the TFT library's "User_Setup.h" file or the gamepad/screen will **not** work!

# Coding your own apps for the shell
NanoShell allows you to utilize the leftover space from flash and RAM (or even optimize it) to make your own apps. Here are a few steps:

1. Create your own icon and make it into a 2bpp image (B00 is transparent, B11 is black, B10 is white and B01 is the palette) (this is done to save on RAM) and put it in ICONS.h
2. Add your own app on the main menu by going to SCREEN.h and finding DrawDesktopI. Here you can find all the routines to draw the main menu. Simply copy an app icon draw statement and add 18 pixels or so to the Y value.
3. To make your app runnable, goto AVRDEFF.h/loop() and find the switch(SelectedApp) case. Add your own app there and write a Start function. Make sure to redraw the desktop once the Start function returns.
4. Create a new header file (e.g. MyCoolApp.h) and add it into the app includes in NANOSHELL.ino right before AVRDEFF.h
5. Create a main function and run it from your Start function.
6. Start coding away!

Good app design should include:
* A main loop for user input
* Reused kernel functionality (to save on RAM)
* **Use the F() macro when possible (for example in tft.print())**

**Once the kernel has started running your app, you can't go back without returning from your main function. (This is similar to regular C++ apps but not exactly. On Windows you can exit out of a console app at any time. Here you can't. So please give the user a chance to exit without resetting if possible, please)
