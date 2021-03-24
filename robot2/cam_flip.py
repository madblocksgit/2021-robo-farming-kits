#include <Wire.h>
#include "PCA9685.h"

#define injectonServo 0
#define injectionElbowServo 1
#define camElbowServo 2
#define camFlipServo 3

PCA9685 driver;
PCA9685_ServoEvaluator pwmServo(102, 470); 

int Imin = 30;
int Imax = 110;

int IEmin = 0;
int IEmax = 40;
int IEIA = 20;

int cEAI=90;
int cEAMin=0;
int cEAMax=180;

int cFAI=90;
int cFAMin=0;
int cFAMax=180;

int angleMap(int r,int a)
{
  if(r==0)
    return(map(a,0,180,90,-90));
  else if(r==1)
    return(map(a,470,102,0,180));
}

//driver.setChannelPWM(driverPinNo,pwmServo.pwmForAngle(angleMap(0,Angle)));

void setup() 
{
  Serial.begin(9600);
  
  Wire.begin();                 
  Wire.setClock(400000);        
  driver.resetDevices();  
  Serial.println("Welcome");      
  driver.init(B000000);         
  driver.setPWMFrequency(50); 

  injectionOff();
  injElbowInitial();
  camEblowInit();
  camFlipInit();
}

void loop() 
{
  camRight();
  delay(1000);
  camLeft();
  delay(1000);

  camFlipUp();
  delay(1000);
  camFlipDown();
  delay(1000);
  
}

void injElbowInitial()
{
  Serial.println("Injection Elbow at Initial angle");
  driver.setChannelPWM(injectionElbowServo,pwmServo.pwmForAngle(angleMap(0,IEIA)));
  delay(1000);
}

void camEblowInit()
{
  Serial.println("Cam Elbow Rotated to Initial Angle");
  driver.setChannelPWM(camElbowServo,pwmServo.pwmForAngle(angleMap(0,cEAI)));
}

void camFlipInit()
{
  Serial.println("Cam Rotated to Initial Angle");
  driver.setChannelPWM(camFlipServo,pwmServo.pwmForAngle(angleMap(0,cFAI)));
}

void injectionOn()
{
   Serial.println("Injection on");
   driver.setChannelPWM(injectionElbowServo,pwmServo.pwmForAngle(angleMap(0,IEIA)));
   delay(1000);
   for(int i = Imin; i <= Imax; i = i+10)
    {
     driver.setChannelPWM(injectonServo,pwmServo.pwmForAngle(angleMap(0,i)));
     delay(20);
    }
}

void injectionOff()
{
  Serial.println("Injection off");
  driver.setChannelPWM(injectonServo,pwmServo.pwmForAngle(angleMap(0,Imin)));
  delay(500);
}

void injElbowDown()
{
  int dummy=angleMap(1,(driver.getChannelPWM(injectionElbowServo)));
  if(dummy+1>IEmax)
    dummy=IEmax;
  Serial.print("Injection Elbow Down, Angle:");
  Serial.println(dummy);
  driver.setChannelPWM(injectionElbowServo,pwmServo.pwmForAngle(angleMap(0,dummy+10)));
}

void injElbowUp()
{
  int dummy=angleMap(1,(driver.getChannelPWM(injectionElbowServo)));
  if(dummy-1<IEmin)
    dummy=IEmin;
  Serial.print("Injection Elbow Up, Angle:");
  Serial.println(dummy);
  driver.setChannelPWM(injectionElbowServo,pwmServo.pwmForAngle(angleMap(0,dummy-10)));
}

void camRight()
{
  int dummy=angleMap(1,(driver.getChannelPWM(camElbowServo)));
  if(dummy+1>cEAMax)
    dummy=cEAMax;
  Serial.print("Cam Right, Angle:");
  Serial.println(dummy);
  driver.setChannelPWM(camElbowServo,pwmServo.pwmForAngle(angleMap(0,dummy+10)));
}

void camLeft()
{
  int dummy=angleMap(1,(driver.getChannelPWM(camElbowServo)));
  if(dummy-1<cEAMin)
    dummy=cEAMin;
  Serial.print("Cam Left, Angle:");
  Serial.println(dummy);
  driver.setChannelPWM(camElbowServo,pwmServo.pwmForAngle(angleMap(0,dummy-10)));
}

void camFlipUp()
{
  int dummy=angleMap(1,(driver.getChannelPWM(camFlipServo)));
  if(dummy+1>cFAMax)
    dummy=cFAMax;
  Serial.print("Cam Flip Up, Angle:");
  Serial.println(dummy);
  driver.setChannelPWM(camFlipServo,pwmServo.pwmForAngle(angleMap(0,dummy+10)));
}

void camFlipDown()
{
  int dummy=angleMap(1,(driver.getChannelPWM(camFlipServo)));
  if(dummy-1<cFAMin)
    dummy=cFAMin;
  Serial.print("Cam Flip Down, Angle:");
  Serial.println(dummy);
  driver.setChannelPWM(camFlipServo,pwmServo.pwmForAngle(angleMap(0,dummy-10)));
}
