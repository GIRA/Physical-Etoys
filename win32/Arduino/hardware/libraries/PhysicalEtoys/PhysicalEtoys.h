#ifndef PhysicalEtoys_h
#define PhysicalEtoys_h

#include "Servo.cpp"

#define PIN_VALUE(x)                (pinValues[(x) - 2])
#define PIN_MODE(x)                  (pinModes[(x) - 2])
#define SERVO(x)                     (myservos[(x) - 2])



long pinValues[18] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
byte pinModes[18] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
Servo myservos[12];

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
  PIN_MODE(pin) = mode;
  if(mode == 0)
    pinMode(pin, INPUT);
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

void attachServo(long pin)
{
  SERVO(pin).attach(pin);
}

void detachServo(long pin)
{
  SERVO(pin).detach();
}

void servoAngle(long pin, long angle)
{
  SERVO(pin).write(minMax(angle, 0, 180));
}



/*	<Cpp fix for "new" operator>	*/
#ifndef cppfix
#define cppfix

__extension__ typedef int __guard __attribute__((mode (__DI__)));

void * operator new(size_t size);
void operator delete(void * ptr);

int __cxa_guard_acquire(__guard *g) {return !*(char *)(g);};
void __cxa_guard_release (__guard *g) {*(char *)g = 1;};
void __cxa_guard_abort (__guard *) {};

void * operator new(size_t size)
{
  return malloc(size);
}

void operator delete(void * ptr)
{
  free(ptr);
}

#endif 
/*	</Cpp fix for "new" operator>	*/


#endif