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

int statusLED=2;
#define LED_ON 1
#define LED_OFF 0

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
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
  pinMode(statusLED,OUTPUT);
  digitalWrite(statusLED,LED_OFF);
  delay(2000);
  Serial.println("Welcome");
  robot_navigate();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  

}

void robot_navigate(void) {
  digitalWrite(br1,brk_release);
  digitalWrite(br2,brk_release);
  digitalWrite(dir1,forward);
  digitalWrite(dir2,forward);
  ledcWrite(0, 1023);
  ledcWrite(1,1023);
  delay(5000);
  digitalWrite(br1,brk);
  digitalWrite(br2,brk);
}
