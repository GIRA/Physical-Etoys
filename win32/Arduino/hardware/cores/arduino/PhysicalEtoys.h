#ifndef PhysicalEtoys_h
#define PhysicalEtoys_h


/* Pin values and modes */
long pinValues[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
byte pinModes[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

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
  return pinModes[pin - 3];
}

void setMode(long pin, byte mode)
{
  pinModes[pin - 3] = mode;
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
    return pinValues[pin - 3];
  }
}

void setValue(long pin, long value)
{
  long actualValue = minMax(value, 0, 255);
  pinValues[pin - 3] = actualValue;
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