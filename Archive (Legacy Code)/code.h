#ifndef  _CODE_H
#define  _CODE_H
typedef unsigned short uint8_t
uint8_t setID(char *attendance){
	attendance[finger.fingerID] = '1';
}

uint8_t checkID(int *attendance){
	int counter = 0x5ffff;
	uint8_t val = finger.getImage();
	while(val != FINGERPRINT_OK){
		//Print FingerPrint has not been detected
		counter--;
		if(counter == 0){
			// No Finger presented
			return 0;
		}
	}
	val = finger.image2Tz();
	if(val != FINGERPRINT_OK)
	{
		//Finger too messy Enter again
		checkID();
	}
		
	val = finger.fingerFastSearch();
	if(val == FINGERPRINT_OK)
	{
		// FingerPrint Found
		setID(attendance);
		return 1;
	}else {
		// FingerPrint not Found
		return 0;
	}
}
#endif