#include "inc/FP_api.h"

SoftwareSerial mySerial(13,15);
Adafruit_Fingerprint FP = Adafruit_Fingerprint(&mySerial);

void setup() {
  FP.begin(57600);
  Serial.begin(9600);
  FP_findModule(FP);
}

void enroll(void) {
  serialFlush();
  Serial.println("Enter your Scholar ID");
  int id = 0;
  while(!Serial.available()){
    id = Serial.parseInt();
  }
  Serial.println("");
  if(id <= 100 && id > 0) {
    Serial.println(id);
    Serial.println("Place your finger on the Scanner");
    while(!FP_fetch(FP)) yield();
    if(FP_img2tz(FP, 1) != true) Serial.println("Error in TZ:1");
    Serial.println("Remove your finger.");
    FP_removeFinger(FP);
    Serial.println("Place again for 2nd scan.");
    while(!FP_fetch(FP)) yield();
    if(FP_img2tz(FP, 2) != true) Serial.println("Error in TZ:2");
    Serial.println("Creating Model");
    FP_model(FP);
    FP_store(FP, id);
    Serial.println("Success");
  }
}

int validate(void) {
  Serial.println("Place your finger on the Scanner");
  while(!FP_fetch(FP)) yield();
  if(FP_validate(FP) != true) return -1;
  int ID;
  FP_ID(FP, ID);
  return ID;
}

void loop() {
  int input = 0;
  serialFlush();
  Serial.println("enroll ? (num > 1 for yes)");
  while(!Serial.available()) {
    input = Serial.parseInt();
    yield();
  }
    
  if(input > 1){
    Serial.println("Enroll Mode");
    enroll();
  }
  else {
    Serial.println("Scan Mode");
    input = 0;
    int ID = validate();
    Serial.print("The scan matches ID# ");
    Serial.println(ID);
  }
}
