// Written by Utkarsh Bhatt on 22.02.2020
// Contains the ready to use API's for the FP Sensor.

#pragma once
#include "SYS_config.h"
#include "SYS_debug.h"
#include <Adafruit_Fingerprint.h>

const char* FP_err2str(uint8_t errCode) {
    switch(errCode) {
        case FINGERPRINT_PACKETRECIEVEERR:
            return "Communications Error";

        case FINGERPRINT_IMAGEFAIL:
            return "Imaging Error";

        case FINGERPRINT_NOFINGER:
            return ".";

        case FINGERPRINT_IMAGEMESS:
            return "Image Too Messy";

        case FINGERPRINT_NOMATCH:
            return "Match not found";

        case FINGERPRINT_FEATUREFAIL:
            return "Couldn't find FP features.";

        case FINGERPRINT_INVALIDIMAGE:
            return "Couldn't find FP features.";

        default:
            return "Unknown Error";
    }
}

bool FP_findModule(Adafruit_Fingerprint &FP) {
    if(FP.verifyPassword()){
        #ifdef _DEBUG_
        postDebug("FP_API", "Module Found.");
        #endif
        sys_delay(50);
        return true;
    } else {
        #ifdef _DEBUG_
        postDebug("FP_API_FIND", "Module not found.");
        #endif
        sys_delay(100);
        return false;
    }
}

bool FP_fetch(Adafruit_Fingerprint &FP) {
	uint8_t status = FP.getImage();  // Fetch FP image.
    if(status != FINGERPRINT_OK) {
        #ifdef _DEBUG_
        postDebug("FP_API_FETCH", FP_err2str(status));
        #endif
        sys_delay(200);
        return false;
    } 
    else {
        sys_delay(100);
        return true;
    }
}

void FP_removeFinger(Adafruit_Fingerprint &FP) {
    uint8_t status = 0;
    while(status != FINGERPRINT_NOFINGER) {
        status = FP.getImage();
        sys_delay(10);
    }
}

bool FP_img2tz(Adafruit_Fingerprint &FP, int ScanNum) {
    // Validates if the fetched Fingerprint is valid or messy.
    uint8_t status = FP.image2Tz(ScanNum);
    if(status != FINGERPRINT_OK) {
        #ifdef _DEBUG_
        postDebug("FP_API_IMG2TZ", FP_err2str(status));
        #endif
        sys_delay(100);
        return false;
    } 
    else {
        sys_delay(50);
        return true;
    }
}

// Does the same thing as the function above but doesnt take any param for the image2TZ.
bool FP_validate(Adafruit_Fingerprint &FP) {
    // Validates if the fetched Fingerprint is valid or messy.
    uint8_t status = FP.image2Tz();
    if(status != FINGERPRINT_OK) {
        #ifdef _DEBUG_
        postDebug("FP_API_VALIDATE", FP_err2str(status));
        #endif
        sys_delay(100);
        return false;
    } 
    else {
        sys_delay(50);
        return true;
    }
}

bool FP_model(Adafruit_Fingerprint &FP) {
    // Converts the validated fingerprint into a store-able model.
    uint8_t status = FP.createModel();
    if(status != FINGERPRINT_OK) {
        #ifdef _DEBUG_
        postDebug("FP_API_MODEL", FP_err2str(status));
        #endif
        sys_delay(100);
        return false;
    } 
    else {
        sys_delay(50);
        return true;
    }
}

bool FP_store(Adafruit_Fingerprint &FP, int ID) {
    // Stores the modelled fingerprint into the provided ID location(1-127).
    // Location 121-127 is by app design reserved for Admins.
    uint8_t status = FP.storeModel(ID);
    if(status != FINGERPRINT_OK) {
        #ifdef _DEBUG_
        postDebug("FP_API_STORE", FP_err2str(status));
        #endif
        sys_delay(100);
        return false;
    } 
    else {
        sys_delay(50);
        return true;
    }
}

//FIX THIS.
bool FP_ID(Adafruit_Fingerprint &FP, int &ID) {
    uint8_t status = FP.fingerFastSearch();
    if(status != FINGERPRINT_OK) {
        #ifdef _DEBUG_
        postDebug("FP_API_ID", FP_err2str(status));
        #endif
        return -1;
    } else {
        ID = FP.fingerID;
        return 1;
    } 
}