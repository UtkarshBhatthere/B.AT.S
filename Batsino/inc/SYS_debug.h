// Written by Utkarsh Bhatt on 22.02.2020
// Contains the debug API for printing Stats at provided Serial.

#pragma once

#ifdef _USE_HW_SERIAL_
    #define debugSerial Serial
#else
    SoftwareSerial debugSerial(debugRX, debugTX);
#endif

#define sys_delay delay

// TODO: Add a timestamp in the Debug message.
void postDebug(const char* debugTag, const char* debugMsg) {
    debugSerial.println("");
    debugSerial.print(debugTag);
    debugSerial.print(" -> ");
    debugSerial.println(debugMsg);
}

void serialFlush(){
  while(Serial.available() > 0) {
    char t = Serial.read();
  }
}
    