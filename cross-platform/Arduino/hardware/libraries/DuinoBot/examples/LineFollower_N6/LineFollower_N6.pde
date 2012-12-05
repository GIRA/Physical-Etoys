#include <MotorDC.h>

//Constante que representa al TRIGGER de detección de línea:
#define TRIGGER				700
#define MOTOR_SPEED			100.0

float s0, s1;

MotorDC motor0(3, 4, 8);
MotorDC motor1(22, 20, 21);
  
void setup()
{
  Serial.begin(9600);
  motor1.setClockwise(false);
  motor0.setSpeed(MOTOR_SPEED);
  motor1.setSpeed(MOTOR_SPEED);
}

void loop()
{

  //Read sensors:
  s0 = analogRead(0);
  s1 = analogRead(1);
  
  /*
  //Debug:
  Serial.print("s0 = ");
  Serial.print(s0);
  Serial.print("/ s1 = ");
  Serial.println(s1);
 ¨*/

  if ( (s0<TRIGGER) && (s1<TRIGGER) )  //00
  {
    motor0.setSpeed(MOTOR_SPEED);
    motor1.setSpeed(MOTOR_SPEED);
  }
  else if ( (s0<TRIGGER) && (s1>TRIGGER) ) //01
  {
    motor0.setSpeed(0.1*MOTOR_SPEED);
    motor1.setSpeed(MOTOR_SPEED);
  }
  else if( (s0>TRIGGER) && (s1<TRIGGER) ) //10
  {
    motor0.setSpeed(MOTOR_SPEED);
    motor1.setSpeed(0.1*MOTOR_SPEED);
  }
  //11: Keeps last state.
}

