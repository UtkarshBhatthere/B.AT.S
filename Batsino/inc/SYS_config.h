// Config Defines.
// This file very smartly manages various build settings for the BATS project.

// Set it 1 or 0 to define whether or not to debug.
#if 1
    #define _DEBUG_
    // Set it 1 or 0 to define whether HW Serial would be used or not.
    #if 1
        #define _USE_HW_SERIAL_
    #else 
        #define debugRX 2   // TODO: Finalise the Pins to be used for the debug Serial.
        #define debugTX 3
    #endif
#endif