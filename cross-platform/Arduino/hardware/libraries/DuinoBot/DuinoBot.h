#ifndef DuinoBot_h
#define DuinoBot_h

#include "Servo.cpp"
#include "MotorDC.h"
#include "IRremote.cpp"

#define PIN_VALUE(x)                (pinValues[(x) - 2]) //  2 to 19
#define PIN_MODE(x)                  (pinModes[(x) - 2]) //  2 to 19
#define SERVO(x)                     (myservos[(x) - 2]) //  2 to 19
#define IR_RECV(x)				 (irReceivers[(x) - 14]) // 14 to 19

#define INPUT_MODE			0
#define OUTPUT_MODE			1
#define PWM_MODE			2
#define SERVO_MODE			3
#define IR_RECV_MODE		4


long pinValues[18] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
byte pinModes[18] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
Servo myservos[12];
IRrecv irReceivers[6];

MotorDC motorDC0(22, 20, 21);
MotorDC motorDC1(3, 4, 8);


long minMax(long, long, long);
long Random(long);

byte getMode(long);
void setMode(long, byte);
long getValue(long);
void setValue(long, long);
bool getBooleanValue(long);
void setBooleanValue(long, bool);
long getDCMotorSpeed(long, long, long);
void setDCMotorSpeed(long, long, long, long);
void setRGMotorSpeed(long, long);
long getRGMotorSpeed(long);
long getIRCode(long);

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
  // First detach any SERVO or IR_RECV
  if(PIN_MODE(pin) == SERVO_MODE)
    SERVO(pin).detach();
  if(PIN_MODE(pin) == IR_RECV_MODE)
    IR_RECV(pin).setPin(0);
  
  // Then, save the new pin mode
  PIN_MODE(pin) = mode;
  
  // Finally, set the actual pin mode
  if(mode == INPUT_MODE)
    pinMode(pin, INPUT);
  else if(mode == SERVO_MODE)
    SERVO(pin).attach(pin);
  else if(mode == IR_RECV_MODE)
	IR_RECV(pin).setPin(pin);
  else // PWM_MODE or OUTPUT_MODE
    pinMode(pin, OUTPUT);
}

long getValue(long pin)
{
  if(getMode(pin) == INPUT_MODE)
  {
    if(pin > 13)
	  return analogRead(pin - 14);
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
    case OUTPUT_MODE:
      digitalWrite(pin, actualValue);
      break;
    case PWM_MODE:
      analogWrite(pin, actualValue);
      break;
	case SERVO_MODE:
	  actualValue = minMax(value, 0, 180);
	  PIN_VALUE(pin) = actualValue;
	  SERVO(pin).write(actualValue);
  }
}

bool getBooleanValue(long pin)
{
  if(getMode(pin) == INPUT_MODE)
  {
    return digitalRead(pin) == 0;	  
  }
  else
  {
    return PIN_VALUE(pin) != 0;
  }
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

long Random(long max)
{
  return random(max);
}

void setRGMotorSpeed(long speed, long motorID)
{
	long actualSpeed = minMax(speed, -100, 100);
	if(motorID == 0)
		motorDC0.setSpeed(actualSpeed);
	if(motorID == 1)
		motorDC1.setSpeed(actualSpeed);
}

long getRGMotorSpeed(long motorID)
{
	if(motorID == 0)
		return motorDC0.getSpeed();
	if(motorID == 1)
		return motorDC1.getSpeed();
}

long previousMillisIR = 0; 
long getIRCode(long pin)
{
	if (millis() - previousMillisIR > 50)
    {
        PIN_VALUE(pin) = (long)IR_RECV(pin).getIRRemoteCode();
        previousMillisIR = millis();   
    }
	return PIN_VALUE(pin);
}

#endif