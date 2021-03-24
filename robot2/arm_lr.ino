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
 * Program Goal       : ARM Control
 ***************************************************************************/

int armL=22;
int armR=23;

int armU=19;
int armD=18;

#define RELAY_ON 0
#define RELAY_OFF 1

void setup() 
{
  pinMode(armL,OUTPUT);
  pinMode(armR,OUTPUT);
  pinMode(armU,OUTPUT);
  pinMode(armD,OUTPUT);
  
  digitalWrite(armL,RELAY_OFF);
  digitalWrite(armR,RELAY_OFF);
  digitalWrite(armU,RELAY_OFF);
  digitalWrite(armD,RELAY_OFF);
  
  Serial.begin(9600);
  Serial.println("WELCOME"); 
  
  
  
}

void loop() {
  
  left();
  delay(1000);
  right();
  delay(1000);

  down();
  delay(1000);
  up();
  delay(1000);
}

void left() {
  for(int i=0;i<10;i++) {
  digitalWrite(armU,RELAY_OFF);
  digitalWrite(armD,RELAY_ON);
  delay(500);
  digitalWrite(armU,RELAY_OFF);
  digitalWrite(armD,RELAY_OFF);
  }
}

void right() {
  for(int i=0;i<10;i++) {
  digitalWrite(armU,RELAY_ON);
  digitalWrite(armD,RELAY_OFF);
  delay(500);
  digitalWrite(armU,RELAY_OFF);
  digitalWrite(armD,RELAY_OFF);
  }
  
}
void up() { // IN1-23, IN2-22
  for(int i=0;i<10;i++) {
  digitalWrite(armL,RELAY_OFF);
  digitalWrite(armR,RELAY_ON);
  delay(100);
  digitalWrite(armL,RELAY_OFF);
  digitalWrite(armR,RELAY_OFF);
  }
}

void down() {
  
  for(int i=0;i<10;i++) {
  digitalWrite(armL,RELAY_ON);
  digitalWrite(armR,RELAY_OFF);
  delay(100);
  digitalWrite(armL,RELAY_OFF);
  digitalWrite(armR,RELAY_OFF);
  }
}
