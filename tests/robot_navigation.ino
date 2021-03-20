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
 * Program Goal       : Robot Navigation
 ***************************************************************************/

// DIR – Pulled down to GND Forward by default and Backward when 5V (logic high) 
// BRK – breaking input to halt the motor in operations when 5V (logic high) 

int dir1=22;
int br1=23;
int pwm1=21;

int dir2=19;
int br2=18;
int pwm2=5;

#define forward 0
#define backward 1

#define brk 1
#define brk_release 0
 
void setup() {

  pinMode(dir1,OUTPUT);
  pinMode(br1,OUTPUT);
  pinMode(dir2,OUTPUT);
  pinMode(br2,OUTPUT);
  digitalWrite(br1,brk);
  digitalWrite(br2,brk);
  
  ledcSetup(0, 50, 10);
  ledcSetup(1, 50, 10);

  ledcAttachPin(pwm1, 0);
  ledcAttachPin(pwm2, 1);

  Serial.begin(9600);
}

void loop() {
  while(Serial.available()) {
    char ch=Serial.read();
    if(ch=='F' || ch=='f') {
      Serial.println("Forward");
      digitalWrite(br1,brk_release);
      digitalWrite(br2,brk_release);
      digitalWrite(dir1,forward);
      digitalWrite(dir2,forward);
      ledcWrite(0, 512);
      ledcWrite(1,512);      
    } else if(ch=='B' || ch=='b') {
      Serial.println("Backward");
      digitalWrite(br1,brk_release);
      digitalWrite(br2,brk_release);
      digitalWrite(dir1,backward);
      digitalWrite(dir2,backward);
      ledcWrite(0, 512);
      ledcWrite(1,512);
    } else if(ch=='L' || ch=='l') {
      Serial.println("Left");
      digitalWrite(br1,brk_release);
      digitalWrite(br2,brk_release);
      digitalWrite(dir1,forward);
      digitalWrite(dir2,backward);
      ledcWrite(0,512);
      ledcWrite(1,512);
    } else if(ch=='R' || ch=='r') {
      Serial.println("Right");
      digitalWrite(br1,brk_release);
      digitalWrite(br2,brk_release);
      digitalWrite(dir1,backward);
      digitalWrite(dir2,forward);
      ledcWrite(0,512);
      ledcWrite(1,512);
    } else if(ch=='S' || ch=='s') {
      Serial.println("Stop");
      digitalWrite(br1,brk);
      digitalWrite(br2,brk);
    }
  }
}

