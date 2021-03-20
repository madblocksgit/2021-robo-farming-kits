/***************************************************************************
 * Project            : Smart Robot Farming
 * Inputs             : Web/Auto
 * Outputs            : Robot Navigation, Seeding, Ploughing
 * Hardware Engineer  : Madhu Parvathaneni
 * Software Engineer  : Madhu Parvathaneni
 * Cloud Engineer     : Madhu Parvathaneni
 * Robot Design       : Venkatesh R
 * Client             : Young Innovations Pvt Ltd - KITS Guntur
 * Date               : 20th March 2021
 * Program Goal       : Ploughing Test
 ***************************************************************************/
int ploughMR=22;
int ploughMB=23;

#define RELAY_ON 0
#define RELAY_OFF 1

void setup() {
  pinMode(ploughMR,OUTPUT);
  pinMode(ploughMB,OUTPUT);
  digitalWrite(ploughMR,RELAY_OFF);
  digitalWrite(ploughMB,RELAY_OFF);
  Serial.begin(9600);
}

void loop() {
 while(Serial.available()) {
  char ch=Serial.read();
  if(ch=='1') {
    Serial.println("Down");
    digitalWrite(ploughMR,RELAY_ON);
    digitalWrite(ploughMB,RELAY_OFF);
    delay(100);
    digitalWrite(ploughMR,RELAY_OFF);
    digitalWrite(ploughMB,RELAY_OFF);
  } else if(ch=='2') {
    Serial.println("Up");
    digitalWrite(ploughMR,RELAY_OFF);
    digitalWrite(ploughMB,RELAY_ON);
    delay(100);
    digitalWrite(ploughMR,RELAY_OFF);
    digitalWrite(ploughMB,RELAY_OFF);
  }
 }
}
