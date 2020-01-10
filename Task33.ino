#include <Arduino.h>


#define MagF            51                     // electromagnet pin
#define buzz_pin        31                     // Buzzer pin
#define RED_pin         43                     //LED Pin
#define Common_pin      45                     //LED Pin
#define GREEN_pin       47                     //LED Pin
#define BLUE_pin        49                     //LED Pin

#define InL1            13                      // motor pin
#define PWML            10                      // PWM motor pin  
#define InL2            9                       // motor pin  

#define InR1            7                       // motor pin
#define PWMR            6                       // PWM motor pin
#define InR2            4                       // motor pin 
int received;
int analogX;
int analogY;
void setup() {
  // initialize serial communications at 9600 bps:
 motor_init();
 MAG_init(); 
 
  Serial.begin(9600);
  
}



void motor_init(void)
{
    //pinMode(MagF, OUTPUT);
    
    pinMode(InL1, OUTPUT);
    pinMode(InL2, OUTPUT);
    pinMode(PWML, OUTPUT);
    
    pinMode(InR1, OUTPUT);
    pinMode(InR2, OUTPUT);
    pinMode(PWMR, OUTPUT);
}
void motorForward_L(int PWM_val)  
{
    analogWrite(PWML, PWM_val);
    digitalWrite(InL1, LOW);
    digitalWrite(InL2, HIGH);
}

void motorForward_R(int PWM_val)  
{
    analogWrite(PWMR, PWM_val);
    digitalWrite(InR1, LOW);
    digitalWrite(InR2, HIGH);
}

void motorBackward_L(int PWM_val)  
{
    analogWrite(PWML, PWM_val);
    digitalWrite(InL1, HIGH);
    digitalWrite(InL2, LOW);
}

void motorBackward_R(int PWM_val)  
{
    analogWrite(PWMR, PWM_val);
    digitalWrite(InR1, HIGH);
    digitalWrite(InR2, LOW);
}


void bothForward()
{
  for(int i=0; i<250; i=i+50)
  {           
        motorForward_R(i);
        motorForward_L(i);  
     
  }
  //delay(100);
}

void bothBackward()
{
  for(int i=0; i<250; i=i+50)
  {           
        motorBackward_R(i);
        motorBackward_L(i);  
  
  }
  //delay(100);
}

void LForwardRBackward()
{
  for(int i=0; i<250; i=i+50)
  {
        motorBackward_R(i);
        motorForward_L(i);  
        
  }
  //delay(100);
}

void LBackwardRForward()
{
  for(int i=0; i<250; i=i+50)
  {
        motorForward_R(i);
        motorBackward_L(i);  
           
  }
  //delay(100);
}
void motorsStop(void)
{
    digitalWrite(InL1, LOW);
    digitalWrite(InL2, LOW);
    digitalWrite(InR1, LOW);
    digitalWrite(InR2, LOW);
    
}

void MAG_init(void)
{
    pinMode(MagF, OUTPUT);
    digitalWrite(MagF, LOW);
}

void MagPick(void)  
{
    digitalWrite(MagF, HIGH);
}

void MagDrop(void)  
{
    digitalWrite(MagF, LOW);
}

void loop()
{
  //Serial.println("first");
   //int Serial_counter = Serial.available();
  if(Serial.available()>=16)
  {
    //Serial.println(Serial.read());
    if(Serial.read()==0x7E)
    {
      for(int i=1 ; i < 11 ; i++)
      {
        byte discardByte = Serial.read();
        
      }
      
      byte digitalMSB = Serial.read();
      byte digitalLSB = Serial.read();
      byte analogMSB1 = Serial.read();
      byte analogLSB1 = Serial.read();
      byte analogMSB2 = Serial.read();
      byte analogLSB2 = Serial.read();
      
      int analogX = analogLSB1+ analogMSB1*256;
      int analogY = analogLSB2+ analogMSB2*256;
      
      Serial.print(analogX);
      Serial.print("\t");
      Serial.println(analogY);
    if((analogX > 1023) || (analogY > 1023 ))
      int a;
    
    else if((analogX > 900)  && (400 < analogY) && (analogY <800 ))
    {
      Serial.println("Both Wheels Forward");
      bothForward();
    }
    else if((analogX > 900) && (analogY < 300) )
    {
      Serial.println("Both wheels Backward");
      bothBackward();
    }
    else if((400< analogX)&&(analogX <800 )&& (analogY > 900) )
    {
      Serial.println("left wheel Backward, right wheel Forward");
      LBackwardRForward();
    }
    else if((analogX < 300) && (analogY > 900))
    {
      Serial.println("left wheel Forward, right wheel Backward");
      LForwardRBackward();
    }
    //else
    //{
    //  motorsStop();
    //}
   
   }
  //Serial.flush();
  
  }
  

  
}
