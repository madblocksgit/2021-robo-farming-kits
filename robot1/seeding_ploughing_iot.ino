/***************************************************************************
 * Project            : Smart Robot Farming
 * Inputs             : Web/Auto
 * Outputs            : Robot Navigation, Ploughing, seeding
 * Hardware Engineer  : Madhu Parvathaneni
 * Software Engineer  : Madhu Parvathaneni
 * Cloud Engineer     : Madhu Parvathaneni
 * Robot Design       : Venkatesh R
 * Client             : Young Innovations Pvt Ltd - KITS Guntur
 * Date               : 20th March 2021
 * Program Goal       : Seeder and Plougher
 ***************************************************************************/
 
#include <WiFi.h>
#include <HTTPClient.h>
#include "StringSplitter.h"

const char* ssid = "Madhu P";
const char* password = "madhu2022";

//Your Domain name with URL path or IP address with path
String serverName = "https://madblocks.tech/XXXXX/XXXXXXX/XXXXX";

int statusLED=2;
#define LED_ON 1
#define LED_OFF 0

int ploughMR=22;
int ploughMB=23;

int seedMR=19;
int seedMB=18;

#define RELAY_ON 0
#define RELAY_OFF 1

unsigned long lastTime = 0;
unsigned long timerDelay = 500;
int cmd=0;

void setup() {
  Serial.begin(9600);
  pinMode(ploughMR,OUTPUT);
  pinMode(ploughMB,OUTPUT);
  pinMode(seedMR,OUTPUT);
  pinMode(seedMB,OUTPUT);
  digitalWrite(seedMR,RELAY_OFF);
  digitalWrite(seedMB,RELAY_OFF);
  digitalWrite(ploughMR,RELAY_OFF);
  digitalWrite(ploughMB,RELAY_OFF);
  pinMode(statusLED,OUTPUT);
  digitalWrite(statusLED,LED_OFF);
  delay(2000);
  Serial.println("Welcome");
  bsp_init();
  digitalWrite(statusLED,LED_ON);
}

void loop() {
  while(cmd==0) {
        cmd=cmd_read_from_madblocksdb();  
        delay(500);
  }
  if(cmd==1) {
    digitalWrite(ploughMR,RELAY_OFF);
    digitalWrite(ploughMB,RELAY_ON);
    delay(100);
    digitalWrite(ploughMR,RELAY_OFF);
    digitalWrite(ploughMB,RELAY_OFF);
    cmd=0;
  } else if(cmd==2) {
    digitalWrite(ploughMR,RELAY_ON);
    digitalWrite(ploughMB,RELAY_OFF);
    delay(100);
    digitalWrite(ploughMR,RELAY_OFF);
    digitalWrite(ploughMB,RELAY_OFF);
    cmd=0;
  } else if(cmd==3) {
    digitalWrite(seedMR,RELAY_ON);
    digitalWrite(seedMB,RELAY_OFF);
    delay(1000);
    digitalWrite(seedMR,RELAY_OFF);
    digitalWrite(seedMB,RELAY_OFF);
    cmd=0;
  } else if(cmd==4) {
    digitalWrite(seedMR,RELAY_OFF);
    digitalWrite(seedMB,RELAY_ON);
    delay(1000);
    digitalWrite(seedMR,RELAY_OFF);
    digitalWrite(seedMB,RELAY_OFF);
    cmd=0;
  } 
}

void bsp_init(void) {
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

int cmd_read_from_madblocksdb(void) {
  int k=0;
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;

      String serverPath = serverName;
      
      // Your Domain name with URL path or IP address with path
      http.begin(serverPath);
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        
        StringSplitter *splitter = new StringSplitter(payload, '#', 3);  
       
        payload=splitter->getItemAtIndex(1);
        payload=payload.substring(2);
        Serial.println(payload);
        if(payload.equals("up"))
          k=1;
        else if(payload.equals("down"))
          k=2;
        else if(payload.equals("left"))
          k=3;
        else if(payload.equals("right"))
          k=4;
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
        ESP.restart();
      }
      // Free resources
      if (http.connected())
         http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
  return(k);
}
