#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include "parse.h"
#include <ESP8266WiFi.h>
#include <Hash.h>
#include "ArduinoJson.h"
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(D2,D3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
Event_TypeDef jsonparse[5];

 char attendance[121];
 uint8_t checkID(int *attendance);
 const char* ssid  = "utkarsh";//";   //replace with your own SSID
 const char* password = "utkarsh123";    //replace with your own
 const char* host = "bats.atwebpages.com";  
 uint8_t checkID(bool *attendance);
 uint8_t setID(bool *attendance);
 int statuss = -1;

#define TFT_CS     D7
#define TFT_RST    D6
#define TFT_DC     D8
#define TFT_SCLK D0
#define TFT_MOSI D1

 Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
 StaticJsonBuffer<200> jsonBuffer;
 WiFiClient client;
  
 bool ServerConnect(void);
 IPAddress ip;
 int i;
 String identify;
void setup() 
{
    // Setting Up the String
    attendance[120] = '\0';
    while(i<121)
      {
        attendance[i]='0';
        i++;
      }
    //Serial Setup.
    Serial.begin(115200);
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    //Wifi Setup
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED)
      {
        delay(500);
        Serial.print(".");
      }
    ip = WiFi.localIP();
    
    Serial.println("");
    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(ip);
    finger.begin(57600);

    // Filling the Screen with Black
    tft.initR(INITR_BLACKTAB); 
    tft.fillScreen(ST7735_BLACK);
    
    pinMode(D5,INPUT_PULLUP);

    // Welcome Message
    tft.setCursor(25, 35);
    tft.setTextSize(2);
    tft.setRotation(3);
    tft.print("Welcome to ");
    tft.setCursor(60,65);
    tft.print("BATS");
    
    delay(1000);

    // Boot Sequence
    tft.setTextSize(2);
    tft.fillScreen(ST7735_BLACK);
    testdrawcircles(10,ST7735_YELLOW);
    tft.fillScreen(ST7735_BLACK);
    tft.drawRect(0,0,159,127, ST7735_GREEN);//col*rows
    tft.setCursor(55,35);
    tft.print("Press");
    tft.drawRect(0,0,159,127, ST7735_GREEN);//col*rows
    tft.setCursor(65,55);
    tft.print("the");
    tft.drawRect(0,0,159,127, ST7735_GREEN);//col*rows
    tft.setCursor(52,75);
    tft.print("Button");
}

void testdrawcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=0; x < tft.width()+radius; x+=radius*2) {
    for (int16_t y=0; y < tft.height()+radius; y+=radius*2) {
      tft.drawCircle(x, y, radius, color);
      delay(10);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
    if(digitalRead(D5)==LOW)
    {
      tft.fillScreen(ST7735_BLACK);
      tft.drawRect(0,0,159,127, ST7735_GREEN);
    
      //col*rows
      tft.setCursor(20,35);
      tft.print("Connecting");
      
      //col*rows
      tft.setCursor(65,55);
      tft.print("to");
     
      //col*rows
      tft.setCursor(53,75);
      tft.print("BATS");
      while( !ServerConnect());
      
      tft.setTextSize(1);
      tft.fillScreen(ST7735_BLACK);
      tft.drawRect(0,0 ,159,25, ST7735_GREEN);
      tft.setCursor(20,13);

      //Event 1
      tft.print(jsonparse[0].Event);
      tft.fillCircle(10,10,5,ST7735_GREEN);
      tft.drawRect(0,25 ,159,25, ST7735_GREEN);
      tft.setCursor(20,37);

      //Event 2
      tft.print(jsonparse[1].Event);
      tft.drawRect(0,50 ,159,25, ST7735_GREEN);
      tft.setCursor(20,62);

      //Event 3
      tft.print(jsonparse[2].Event);
      tft.drawRect(0,75,159,25, ST7735_GREEN);
      tft.setCursor(20,87);

      //Event 4
      tft.print(jsonparse[3].Event);
      tft.drawRect(0,100,159,25, ST7735_GREEN);
      tft.setCursor(20,113);

      //Event 5
      tft.print(jsonparse[4].Event);
      
      int a=0,i=0;
      while(digitalRead(D5)==HIGH){yield();}
        while(a!=1)
        {
         if(a==2)
         {
           tft.fillCircle(10,10+25*i,5,ST7735_BLACK);
           i++;
           if(i>4)i=0;
           tft.fillCircle(10,10+25*i,5,ST7735_GREEN); 
           Serial.println("Yo");
         }
         a=Select();
         yield();
        }

      int select = i;
      tft.fillScreen(ST7735_BLACK);
      tft.setCursor(55, 75);
      tft.print(i);
      
//      JsonObject &eventid= jsonBuffer.createObject();
//      eventid["event_id"] = i;
      
      //senddata(eventid,url);
      delay(2000);
      tft.fillScreen(ST7735_BLACK);
      tft.setTextSize(2);
      tft.drawRect(0,0,159,127, ST7735_GREEN);
      
      //col*rows
      tft.setCursor(10,35);
      tft.print("Press Button");
      
      //col*rows
      tft.setCursor(65,55);
      tft.print("to");
      
      //col*rows
      tft.setCursor(53,75);
      tft.print("Start");
      tft.setTextSize(1);
      i=0;
      while(digitalRead(D5)==HIGH){yield();}
        checkID(attendance);
      while(i< 121){
         if(statuss==5)
         break;

        tft.fillScreen(ST7735_BLACK);
        tft.drawRect(0,0,159,127, ST7735_GREEN);
        
        //col*rows
        tft.setCursor(10,35);
        tft.setTextSize(2);
        tft.print("Press Button");
        
        //col*rows
        tft.setCursor(65,55);
        tft.print("to");
        
        //col*rows
        tft.setCursor(48,75);
        tft.print("Proceed");
        tft.setTextSize(1);
        while(digitalRead(D5)==HIGH){yield();}
        statuss = checkID(attendance);
        }

        
        Serial.println("Check");

        String at = (String)attendance;
        Serial.println(at);

        Serial.println("Check2");
        JsonObject &eventid= jsonBuffer.createObject();
        eventid["id"] = "1614";
        eventid["schid"] = at.c_str() ;
        eventid["eventid"] = jsonparse[select].Event;
    //        eventid.prettyPrintTo(arr, sizeof(eventid));
    //        Serial.println(arr);
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
      Serial.println("connection failed");
      
    }
    senddata(eventid,"/service2.php");
                    
    unsigned long timeout = millis();
    while (client.available() == 0) {
    if (millis() - timeout > 5000) {
    Serial.println(">>> Client Timeout !");
    client.stop();
          
      }
    }
      String line1;
      line1 = client.readStringUntil('\0');
      Serial.println("response");
      Serial.println(line1);
        //Ho gya sab!
      }
}

int Select(void)
{
  int counter = 0;
  if(digitalRead(D5)==LOW)
  {
   while(digitalRead(D5)==LOW)
    {
      counter++;
      Serial.println(counter);
      delay(100);
    }
    if(counter > 5)
    {
      Serial.println("The return is 1");
      return 1;
    }
    else
    {
     Serial.println("The return is 2");
     return 2;
    }
  }
  return 0;
}

void senddata(JsonObject& root,String url)
{ 
    char JSONmessageBuffer[200];
    root.prettyPrintTo(JSONmessageBuffer, 200);
    String ar = (String)JSONmessageBuffer;
    //parseString(JSONmessageBuffer,jsonparse);
    Serial.println(ar);
    Serial.println(ar.length());
    client.print("POST " + url + " HTTP/1.1\r\n" +
                   "Host: " + host + "\r\n" + 
                   "Connection: close\r\n");
    client.print("Content-Type: application/json\r\n");
    client.print("Content-Length: ");
    client.print(ar.length());
    client.print("\r\n");
    client.println();
    client.println(ar);
    client.print("\n");
}

bool ServerConnect(void)
{
    Serial.print("connecting to ");
    Serial.println(host);
    // Use WiFiClient class to create TCP connections
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
      Serial.println("connection failed");
      return 4;
    }
    identify = "1614";
    
    //hash = sha1(identify+"BioMetriC"); 
    
    JsonObject& root = jsonBuffer.createObject();
    root["id"] = identify;
    //root["hash"] = hash;
    senddata(root,"/service1.php");
    //client.print(str + "\n");
    /*
     * schid: "00000000000"
     * eventid: "Maths Class"
     * id: 1615
     * 
     */
    
    /*  client.print("Content-Type: application/json\r\n"); 
      client.print("Content-Length: 42 \r\n");
      client.println(); 
      client.print(JSONmessageBuffer); */
     
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 15000) {
          Serial.println(">>> Client Timeout !");
          client.stop();
          return 0;
      }
    }
    String line;
      delay(100);
      for(i=0;i<8;i++){
       line = client.readStringUntil('\n');
      Serial.println(line);
      }
      //Serial.print("Data Sent!");
      //
      line = client.readStringUntil('\n');
      Serial.println(line);
      char *line2 = (char*)line.c_str();
      Serial.println("The json response is");
      parseString(line2,jsonparse);
      Serial.println(jsonparse[0].Event);
      Serial.println(jsonparse[1].Event);
      Serial.println(jsonparse[2].Event);
      Serial.println(jsonparse[3].Event);
      Serial.println(jsonparse[4].Event);
      //parse the char array here
    return 1;
}

//typedef unsigned short uint8_t;
uint8_t setID(char *attendance){
    attendance[finger.fingerID-1] = '1';
}

uint8_t checkID(char *attendance){
   uint8_t val = finger.getImage();
   unsigned long timeout = millis();
   tft.fillScreen(ST7735_BLACK);
   tft.drawRect(0,0,159,127, ST7735_GREEN);//col*rows
   tft.setCursor(35,35);
   tft.setTextSize(2);
   tft.print("Put your");
   //col*rows
   tft.setCursor(48,55);
   tft.print("Finger");
   tft.setTextSize(1);
   while(val != FINGERPRINT_OK){
      val = finger.getImage();
      if(millis() - timeout > 10000){
          tft.fillScreen(ST7735_BLACK);
          tft.drawRect(0,0,159,127, ST7735_GREEN);//col*rows
          tft.setCursor(20,35);
          tft.setTextSize(2);
          tft.print("No Finger");
          //col*rows
          tft.setCursor(20,55);
          tft.print("Presented!");
          tft.setTextSize(1);
          delay(1500);
          return 0;
      }
      yield();
  }
  val = finger.image2Tz();
  if(val != FINGERPRINT_OK)
  {
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(30, 55);
    tft.print("Finger too messy");
     delay(1500);
    checkID(attendance);
  }
    
  val = finger.fingerFastSearch();
  if(val == FINGERPRINT_OK)
  {
    if(finger.fingerID == 121)
    {
        tft.fillScreen(ST7735_BLACK);
        tft.setCursor(30,50);
        tft.print("Process Completed");
        delay(500);
        return 5; 
    }
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(30,50);
    tft.print("Attendance Stored");
    tft.setCursor(0, 100);
    tft.print("Scan Admin's Finger to STOP!");
    delay(1500);
    setID(attendance);
    i++;
    Serial.println(attendance);
    return 1;
  }else {
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(10, 50);
    tft.print("No Fingerprint Found!");
    tft.setCursor(10, 80);
    tft.print("Attendance Not Marked!");
    delay(1500);
    return 0;
  }
}


