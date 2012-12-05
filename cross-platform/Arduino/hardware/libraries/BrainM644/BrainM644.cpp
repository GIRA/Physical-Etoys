
#include "BrainM644.h"

// Creates two instances of the MotorDC class, specifying
// the pins for Enable, D0 and D1 bits for the brain's
// integrated dual H-Bridge:
MotorDC motor0 = MotorDC(13, 14, 15);
MotorDC motor1 = MotorDC(12, 22, 23);
