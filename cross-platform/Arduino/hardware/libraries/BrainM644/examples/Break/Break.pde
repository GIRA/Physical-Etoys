#include "BrainM644.h"

void setup()
{
motor0.setClockwise(true);
motor0.setClockwise(false);

motor0.setSpeed(100.0);
motor1.setSpeed(100.0);

delay(5000);

motor0.brake();
motor1.setSpeed(0);
}

void loop()
{

}
