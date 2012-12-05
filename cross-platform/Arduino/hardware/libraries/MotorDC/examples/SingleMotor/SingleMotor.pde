/*
 * SingleMotor
 *
 * A single DC motor with speed proportional to analog input 1.
 *
 *
 * Created 2010.04.06 (yyyy.mm.dd)
 * By Julián da Silva Gillig @ RobotGroup.
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
MotorDC motorDC(13, 14, 15);


void setup()
{
  Serial.begin(115200); 
}

void loop()
{
  // Get the sensor value and adjusts the range to (-100.0 to +100.0):
  float speed = (analogRead(1)*200.0/1023.0)-100.0;

  Serial.println(speed
  );
  delay(10);

  // Set  the motor speed:
  motorDC.setSpeed(speed);
}
