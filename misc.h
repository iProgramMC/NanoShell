/*
  NanoShell - MISC.H -> Miscellaneous functions

  Copyright (c) iProgramInCpp 2019.
  Library (c) Adafruit Industries, Bodmer.
*/

void ExecuteDialogAction()
{
  switch (dlg_type) {
    case DLGTYPE_FORMAT:
      ClearEEPROM();
      break;
    case DLGTYPE_ABOUT:break;
    default:
      Serial.print(F("Could not find dialog type "));
      Serial.println(dlg_type);
  }
}
