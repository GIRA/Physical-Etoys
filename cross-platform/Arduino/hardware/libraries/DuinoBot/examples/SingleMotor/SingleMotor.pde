/*
 * SingleMotor
 *
 * A single DC motor with speed proportional to analog input 1.
 *
 *
 * Created 2010.04.06 (yyyy.mm.dd)
 * By Juli�n da Silva Gillig @ RobotGroup.
 *
 * http://multiplo.org
 * http://robotgroup.com.ar
 *
 * License: The RobotGroup Pacifist License.
 */

#include <MotorDC.h>

// change this to the number of steps on your motor
#define STEPS 100

// Creates an instance of the MotorDC class, specifying
// the pins for Enable, D0 and D1 bits for the H-Bridge:
MotorDC motorDC0(3, 4, 8);
MotorDC motorDC1(22, 20, 21);


void setup()
{
  Serial.begin(115200); 
}

void loop()
{
//  motorDC0.setClockwise(false);
  motorDC0.setSpeed(100);
  motorDC1.setSpeed(100);
}
