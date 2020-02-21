// Written by Utkarsh Bhatt on 22.02.2020
// Contains the ready to use API's for the FP Sensor.

#pragma once
#include <Adafruit_Fingerprint.h>
#include "SYS_debug.h"

const char* FP_err2str(uint8_t errCode) {
    switch(errCode):
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

bool FP_fetch(Adafruit_Fingerprint FP) {
	uint8_t status = FP.getImage();  // Fetch FP image.
    if(status != FINGERPRINT_OK) {
        postDebug("FP_API", FP_err2str(status));
        return false;
    } 
    else {
        return true;
    }
}

bool FP_validate(Adafruit_Fingerprint FP) {
    // Validates if the fetched Fingerprint is valid or messy.
    uint8_t status = FP.image2Tz();
    if(status != FINGERPRINT_OK) {
        postDebug("FP_API", FP_err2str(status));
        return false;
    } 
    else {
        return true;
    }
}

bool FP_model(Adafruit_Fingerprint FP) {
    // Converts the validated fingerprint into a store-able model.
    uint8_t status = FP.createModel();
    if(status != FINGERPRINT_OK) {
        postDebug("FP_API", FP_err2str(status));
        return false;
    } 
    else {
        return true;
    }
}

bool FP_store(Adafruit_Fingerprint FP, int ID) {
    // Stores the modelled fingerprint into the provided ID location(1-127).
    // Location 121-127 is by app design reserved for Admins.
    uint8_t status = FP.storeModel(ID);
    if(status != FINGERPRINT_OK) {
        postDebug("FP_API", FP_err2str(status));
        return false;
    } 
    else {
        return true;
    }
}

bool FP_ID(Adafruit_Fingerprint FP) {
    uint8_t status = FP.fingerFastSearch();
    if(status != FINGERPRINT_OK) {
        postDebug("FP_API", FP_err2str(status));
        return false;
    } 
    else {
        return true;
    }
}