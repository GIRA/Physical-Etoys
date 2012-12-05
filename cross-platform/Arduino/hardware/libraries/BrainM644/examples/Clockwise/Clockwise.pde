#include "BrainM644.h"

void setup()
{
motor0.setClockwise(true);
motor0.setClockwise(false);

motor0.setSpeed(50.0);
motor1.setSpeed(50.0);

delay(5000);

motor0.setSpeed(0);
motor1.setSpeed(0);
}

void loop()
{

}
