// Written by Utkarsh Bhatt on 22.02.2020
// Contains the debug API for printing Stats at provided Serial.

#pragma once

#ifdef __USE_HW_SERIAL_
    #define debugSerial Serial
#else
    #define debugRX 2   // TODO: Finalise the Pins to be used for the debug Serial.
    #define debugTX 3   // TODO: Move all config settings to a separate file.
    SoftwareSerial debugSerial(debugRX, debugTX);
#endif
// TODO: Add a timestamp in the Debug message.
void postDebug(const char* debugTag, const char* debugMsg) {
    debugSerial.print(debugTag);
    debugSerial.print(" -> ");
    debugSerial.println(debugMsg);
}
    