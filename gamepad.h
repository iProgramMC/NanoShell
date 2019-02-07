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
