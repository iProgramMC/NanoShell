/*
  NanoShell - DEBUG.H -> Debug functions.

  Copyright (c) iProgramInCpp 2019.
  Library (c) Adafruit Industries, Bodmer.
*/

int getFreeMemory()
{
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

// Jumps to address 0 (start of FLASH)
// which, in turn, resets the device.
void reset_system()
{
  asm volatile("jmp 0");
}
