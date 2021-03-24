
/***************************************************************************
 * Project            : Smart Robot Farming
 * Inputs             : Bluetooth
 * Outputs            : Plucking Mechanism
 * Hardware Engineer  : Madhu Parvathaneni
 * Software Engineer  : Madhu Parvathaneni
 * Cloud Engineer     : Madhu Parvathaneni
 * Robot Design       : Venkatesh R
 * Client             : Young Innovations Pvt Ltd - KITS Guntur
 * Date               : 20th March 2021
 * Program Goal       : Robot Navigation
 ***************************************************************************/
#include <Servo.h>

Servo leftServo;
Servo rightServo;

int ls=9;
int rs=6;
int k=0;

int dir1=2;
int pwm1=3;
int br1=4;

#define forward 0
#define backward 1

#define brk 1
#define brk_release 0

int statusLED=13;

#define LED_ON 1
#define LED_OFF 0

#define RELAY_ON 0
#define RELAY_OFF 1

int mR=11;
int mB=10;

void setup() {
  leftServo.attach(9);
  rightServo.attach(6);
  Serial.begin(9600);
  leftServo.write(0);
  rightServo.write(0);
  Serial.println("Welcome");
  
  pinMode(dir1,OUTPUT);
  pinMode(pwm1,OUTPUT);
  pinMode(br1,OUTPUT);
  pinMode(statusLED,OUTPUT);
  pinMode(mR,OUTPUT);
  pinMode(mB,OUTPUT);
  digitalWrite(mR,RELAY_OFF);
  digitalWrite(mB,RELAY_OFF);
}

void loop() {
  digitalWrite(statusLED,LED_ON);
  while(!Serial.available());
  while(Serial.available()) {
    char ch=Serial.read();
    if(ch=='1') {
      Serial.println("Start");
      startRobot();
    } else if(ch=='2') {
      Serial.println("Reverse");
      reverseRobot();
    } else if(ch=='3') {
      Serial.println("Stop");
      stopRobot();
    } else if(ch=='4') {
      Serial.println("ARM Left");
      armLeft();
    } else if(ch=='5') {
      Serial.println("ARM Right");
      armRight();
    } else if(ch=='6') {
      int k=leftServo.read();
      Serial.println(k);
      if(k<170)
        leftServo.write(k+10);
      else
        leftServo.write(0);        
    } else if(ch=='7') {
      int k=leftServo.read();
      Serial.println(k);
      if(k>0) 
        leftServo.write(k-10);
      else
        leftServo.write(0);
    } else if(ch=='8') {
      int k=rightServo.read();
      Serial.println(k);
      if(k<170)
        rightServo.write(k+10);
      else
        rightServo.write(0);        
    } else if(ch=='9') {
      int k=rightServo.read();
      Serial.println(k);
      if(k>0) 
        rightServo.write(k-10);
      else
        rightServo.write(0);
    }
  }
}

void startRobot(void) {
  digitalWrite(dir1,forward);
  digitalWrite(br1,brk_release);
  analogWrite(pwm1,255);
}

void reverseRobot(void) {
  digitalWrite(dir1,backward);
  digitalWrite(br1,brk_release);
  analogWrite(pwm1,255);
}

void stopRobot(void) {
  digitalWrite(br1,brk);
}

void armLeft(void) {
  digitalWrite(mR,RELAY_ON);
  digitalWrite(mB,RELAY_OFF);
  delay(200);
  digitalWrite(mR,RELAY_OFF);
  digitalWrite(mB,RELAY_OFF);
}

void armRight(void) {
  digitalWrite(mR,RELAY_OFF);
  digitalWrite(mB,RELAY_ON);
  delay(200);
  digitalWrite(mR,RELAY_OFF);
  digitalWrite(mB,RELAY_OFF);
}

