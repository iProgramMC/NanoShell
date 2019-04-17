# NanoShell for Arduino

WARNING: requires 1.5k of RAM, so be careful about which microcontroller you put it on!
Technically, it should work on a MEGA 2560, but I haven't tried it yet.

edit: it does work on a MEGA but the raw code doesn't compile for the UNO because of flash related problems.
Please remove all branding icons (a_png*) except a_png0 and a_png1, and the draw code related to it.

Source and pictures can be found here and, hopefully, only here.

## Acknowledgements

It uses Bodmer/TFT_ST7735 (and possibly adafruit/Adafruit-GFX-Library) libraries.
It also uses EEPROM.h and SPI.h.

## Built with:
* [Arduino IDE](https://arduino.cc)

## Authors
* [iProgramInCpp](https://github.com/iprogrammc)

See also the list of [contributors](https://github.com/iprogrammc/nanoshell/contributors) who participated in this project.

## Licensing
This project is licensed under the MIT License, which should be provided [here](LICENSE.txt).

## Instructions
These instructions will help you make yourself a device able to run NanoShell (assuming you've got the right components) for development and testing purposes.

### Connecting a few buttons
Make sure that the buttons are normally open and are momentary switches.

* UP -> Arduino pin 2, 
* DOWN -> Arduino pin 3, 
* LEFT -> Arduino pin 4, 
* RIGHT -> Arduino pin 5, 
* A Button -> Arduino pin 6, 
* B Button -> Arduino pin 12.

### Connecting the LCD
* RST -> Arduino pin 7, 
* CS -> Arduino pin 9, 
* D/C -> Arduino pin 8, 
* DIN -> Arduino pin 11, 
* CLK -> Arduino pin 13, 

**WARNING**: Please change to these pins in the TFT library's "User_Setup.h" file or the screen will **not** work properly!

### Coding your own apps for the shell
NanoShell allows you to utilize the leftover space from flash and RAM (or even optimize it) to make your own apps. Here are a few steps:

1. Create your own icon and make it into a 2bpp image (B00 is transparent, B11 is black, B10 is white and B01 is the palette defined color) (this is done to save on RAM) and put it in `ICONS.h`
2. Add your own app on the main menu by going to `SCREEN.h` and finding `DrawDesktopI()`. Here you can find all the routines to draw the main menu. Simply copy an app icon draw statement and add 18 pixels or so to the Y value.
3. To make your app runnable, goto `AVRDEFF.h/loop()` and find the `switch(SelectedApp)` case. Add your own app there and write a Start function. Make sure to redraw the desktop once the `Start` function returns. After that, go to SCREEN.h and add 1 to `APP_COUNT`. You'll need this to be able to select and run your app.
4. Create a new header file (e.g. `MyCoolApp.h`) and add it into the app includes in `NANOSHELL.ino` right before AVRDEFF.h
5. Create a main function and run it from your Start function.
6. Start coding away!

Good app design should include:
* A main loop for user input
* Reused kernel functionality (to save on RAM)
* **Use the `F()` macro when possible (for example in `tft.print()`)**

## Extra Info

Once the kernel has started running your app, you can't go back without returning from your main function. (This is similar to regular apps but not exactly) 
On Windows you can request an exit out of an app at any time. Here you can't. So please give the user a chance to exit without resetting if possible, please :)
