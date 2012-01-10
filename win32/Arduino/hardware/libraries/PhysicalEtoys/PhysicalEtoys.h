#ifndef PhysicalEtoys_h
#define PhysicalEtoys_h

#include "Servo.cpp"

#define PIN_VALUE(x)                (pinValues[(x) - 2])
#define PIN_MODE(x)                  (pinModes[(x) - 2])
#define SERVO(x)                     (myservos[(x) - 2])

/* Modes:
	0 --- INPUT
	1 --- OUTPUT
	2 --- PWM
	3 --- SERVO
*/

long pinValues[18] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
byte pinModes[18] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
Servo myservos[12];


long minMax(long, long, long);
byte getMode(long);
void setMode(long, byte);
long getValue(long);
void setValue(long, long);
bool getBooleanValue(long);
void setBooleanValue(long, bool);
long getDCMotorSpeed(long, long, long);
void setDCMotorSpeed(long, long, long, long);


long minMax(long value, long min, long max)
{
  if(value > max)
    return max;
  if(value < min)
    return min;
  return value;
}

byte getMode(long pin)
{
  return PIN_MODE(pin);
}

void setMode(long pin, byte mode)
{
  if(PIN_MODE(pin) == 3)
    SERVO(pin).detach();
  PIN_MODE(pin) = mode;
  if(mode == 0)
    pinMode(pin, INPUT);
  else if(mode == 3)
    SERVO(pin).attach(pin);
  else
    pinMode(pin, OUTPUT);
}

long getValue(long pin)
{
  if(getMode(pin) == 0)
  {
    if(pin > 13)
	  return analogRead(pin);
	else
      return digitalRead(pin);
  }
  else
  {
    return PIN_VALUE(pin);
  }
}

void setValue(long pin, long value)
{
  long actualValue = minMax(value, 0, 255);
  PIN_VALUE(pin) = actualValue;
  switch(getMode(pin))
  {
    case 1: //OUT
      digitalWrite(pin, actualValue);
      break;
    case 2: //PWM
      analogWrite(pin, actualValue);
      break;
	case 3: //SERVO
	  actualValue = minMax(value, 0, 180);
	  PIN_VALUE(pin) = actualValue;
	  SERVO(pin).write(actualValue);
  }
}

bool getBooleanValue(long pin)
{
  return getValue(pin) != 0;
}

void setBooleanValue(long pin, bool value)
{
  if(value)
    setValue(pin, 1);
  else
    setValue(pin, 0);
}

long getDCMotorSpeed(long d0, long d1, long en)
{
  return getValue(en);
}

void setDCMotorSpeed(long speed, long d0, long d1, long en)
{
  long actualSpeed = minMax(speed, -100, 100);
  if(actualSpeed < 0)
  {
	setValue(d0, 0);
	setValue(d1, 1);
  }
  else
  {
    setValue(d0, 1);
	setValue(d1, 0);
  }
  setValue(en, abs(actualSpeed) / 100 * 255);
  PIN_VALUE(en) = actualSpeed;
}


#endif