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
 * Program Goal       : Seeding Test
 ***************************************************************************/
int seedMR=2;
int seedMB=15;

#define RELAY_ON 0
#define RELAY_OFF 1

void setup() {
  pinMode(seedMR,OUTPUT);
  pinMode(seedMB,OUTPUT);
  digitalWrite(seedMR,RELAY_OFF);
  digitalWrite(seedMB,RELAY_OFF);
  Serial.begin(9600);
}

void loop() {
 while(Serial.available()) {
  char ch=Serial.read();
  if(ch=='1') {
    Serial.println("Left");
    digitalWrite(seedMR,RELAY_ON);
    digitalWrite(seedMB,RELAY_OFF);
    delay(1000);
    digitalWrite(seedMR,RELAY_OFF);
    digitalWrite(seedMB,RELAY_OFF);
  } else if(ch=='2') {
    Serial.println("Right");
    digitalWrite(seedMR,RELAY_OFF);
    digitalWrite(seedMB,RELAY_ON);
    delay(1000);
    digitalWrite(seedMR,RELAY_OFF);
    digitalWrite(seedMB,RELAY_OFF);
  }
 }
}
