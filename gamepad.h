/*
  NanoShell - GAMEPAD.H -> Built-in library for the GamePad.

  Copyright (c) iProgramInCpp 2019.
  Library (c) Adafruit Industries, Bodmer.
*/

#define UP_PIN 2
#define DN_PIN 3
#define LT_PIN 4
#define RT_PIN 5
#define AB_PIN 6
#define BB_PIN 12

#define UP_BUTTON    0B01000000
#define DOWN_BUTTON  0B00100000
#define LEFT_BUTTON  0B00010000
#define RIGHT_BUTTON 0B00001000
#define A_BUTTON     0B00000100
#define B_BUTTON     0B00000010


uint8_t prevGPState = 0;

uint8_t GetControllerState()
{
  uint8_t i = 0;
  bool state = 0;

  state = digitalRead(UP_PIN);
  i += !state; i <<= 1;
  state = digitalRead(DN_PIN);
  i += !state; i <<= 1;
  state = digitalRead(LT_PIN);
  i += !state; i <<= 1;
  state = digitalRead(RT_PIN);
  i += !state; i <<= 1;
  state = digitalRead(AB_PIN);
  i += !state; i <<= 1;
  state = digitalRead(BB_PIN);
  i += !state; i <<= 1;


  return i;
}

uint8_t InitializeGamepad()
{
  pinMode(UP_PIN, INPUT_PULLUP);
  pinMode(DN_PIN, INPUT_PULLUP);
  pinMode(LT_PIN, INPUT_PULLUP);
  pinMode(RT_PIN, INPUT_PULLUP);
  pinMode(BB_PIN, INPUT_PULLUP);
  pinMode(AB_PIN, INPUT_PULLUP);
}
