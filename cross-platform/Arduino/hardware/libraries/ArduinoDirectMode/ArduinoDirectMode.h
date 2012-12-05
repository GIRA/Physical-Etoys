#include "QueueArray.h"
#include "WString.cpp" //Why do I need to include this?!? #Richo
#include "Servo.cpp"


/* REQUEST COMMANDS */
#define RQ_ACTIVATE_ANALOG_PIN                         0
#define RQ_ANALOG_WRITE                                1
#define RQ_ACTIVATE_DIGITAL_PORT                       2
#define RQ_DIGITAL_PIN_MODE                            3
#define RQ_DIGITAL_WRITE                               4
#define RQ_ATTACH_SERVO                                5
#define RQ_SERVO_ANGLE                                 6
#define RQ_DETACH_SERVO                                7

#define RQ_MOTORDC                                     8

/* RESPONSE COMMANDS */
#define RS_DIGITAL_PORT                                1
#define RS_ANALOG_PIN                                  2
#define RS_VERSION                                     3


/* MACROS */
#define IS_COMMAND(x)                    ((x) >> 7 == 0)
#define IS_ARGUMENT(x)                   ((x) >> 7 == 1)
#define GET_COMMAND(x)                               (x)
#define GET_ARGUMENT(x)                      ((x) & 127)
#define AS_COMMAND(x)                                (x)
#define AS_ARGUMENT(x)                       ((x) | 128)
#define SERVO(x)                     (myservos[(x) - 2])


extern "C" void __cxa_pure_virtual() {} //Why do I need to include this?!? #Richo


bool reportAnalogPin[6] = {false, false, false, false, false, false};
bool reportDigitalPort[2] = {false, false};
bool reportDigitalPin[12] = {false, false, false, false, false, false, false, false, false, false, false, false};
Servo myservos[12];

long previousMillis = 0; 
long interval = 15;


int argsToRead = -1;
QueueArray <byte> queue;


void establishContact();
void readCommand(byte);
void setArgsToReadFor(byte);
void readArgument(byte);
void executeCommand();
void executeDigitalWrite();
void executeDigitalPinMode();
void executeAnalogWrite();
void executeActivateDigitalPort();
void executeActivateAnalogPin();
void sendValues();
void sendDigitalValues();
void sendAnalogValues();
Servo servo(long);
void executeAttachServo();
void executeDetachServo();
void executeServoAngle();


void setup()
{
    Serial.begin(57600);
	establishContact();
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("HOLA, SOY ARDUINO");
    delay(300);
  }
}

void loop()
{
    if(Serial.available())
    {
       byte inByte = Serial.read();
       
       if(IS_COMMAND(inByte))
           readCommand(inByte);
       if(IS_ARGUMENT(inByte))
           readArgument(inByte);
       
       if(argsToRead == 0)
           executeCommand();
    }
    
    if (millis() - previousMillis > interval)
    {
        sendValues();
        previousMillis = millis();   
    }
}

void readCommand(byte inByte)
{
    while(!queue.isEmpty())
        queue.pop();
    byte command = GET_COMMAND(inByte);
    queue.push(command);
    setArgsToReadFor(command);
}

void setArgsToReadFor(byte command)
{
    switch(command)
    {
        case RQ_ANALOG_WRITE:
		case RQ_SERVO_ANGLE:
            argsToRead = 3;
            break;
        case RQ_ACTIVATE_ANALOG_PIN:
        case RQ_ACTIVATE_DIGITAL_PORT:
        case RQ_DIGITAL_WRITE:
        case RQ_DIGITAL_PIN_MODE:
			argsToRead = 2;
            break;         
		case RQ_ATTACH_SERVO:
		case RQ_DETACH_SERVO:
            argsToRead = 1;
            break;         
    }
}

void readArgument(byte inByte)
{
    byte argument = GET_ARGUMENT(inByte);
    queue.push(argument);
    argsToRead--;
}

void executeCommand()
{
    switch(queue.pop())
    {
        case RQ_DIGITAL_WRITE:
            executeDigitalWrite();
            break;
        case RQ_DIGITAL_PIN_MODE:
            executeDigitalPinMode();
            break;
        case RQ_ANALOG_WRITE:
            executeAnalogWrite();
            break;
        case RQ_ACTIVATE_DIGITAL_PORT:
            executeActivateDigitalPort();
            break;
        case RQ_ACTIVATE_ANALOG_PIN:
            executeActivateAnalogPin();
            break;
		case RQ_ATTACH_SERVO:
			executeAttachServo();
			break;
		case RQ_DETACH_SERVO:
			executeDetachServo();
			break;
		case RQ_SERVO_ANGLE:
			executeServoAngle();
			break;
    }
    argsToRead = -1;
}

void executeDigitalWrite()
{
    byte pin = queue.pop();
    byte value = queue.pop();
    digitalWrite(pin, value);
}

void executeDigitalPinMode()
{
    byte pin = queue.pop();
    byte value = queue.pop();
    pinMode(pin, value);
    reportDigitalPin[pin] = (value == 0);
}

void executeAnalogWrite()
{
    byte pin = queue.pop();
    byte value1 = queue.pop();
    byte value2 = queue.pop();
    byte value = value1 | (value2 << 7);
	
    analogWrite(pin, value);
}


void executeActivateDigitalPort()
{
    byte port = queue.pop();
    byte value = queue.pop();
    
    reportDigitalPort[port] = (value != 0);
}

void executeActivateAnalogPin()
{
    byte pin = queue.pop();
    byte value = queue.pop();
    
    reportAnalogPin[pin] = (value != 0);
}

void executeAttachServo()
{
	byte pin = queue.pop();
	
	SERVO(pin).attach(pin);
}

void executeDetachServo()
{
	byte pin = queue.pop();
	
	SERVO(pin).detach();	
}

void executeServoAngle()
{
	byte pin = queue.pop();
	byte value1 = queue.pop();
    byte value2 = queue.pop();
    byte value = value1 | (value2 << 7);
	
	SERVO(pin).write(value);
}


void sendValues()
{
    sendDigitalValues();
    sendAnalogValues();
}

void sendDigitalValues()
{
    for(int port = 0; port < 2; port++)
    {
        if(reportDigitalPort[port])
        {
            Serial.print(AS_COMMAND(RS_DIGITAL_PORT), BYTE);            
            Serial.print(AS_ARGUMENT(port), BYTE);
            
            byte pin;
            byte value = 0;
            if(reportDigitalPin[pin = 2 + (6 * port)])
              value |= digitalRead(pin);
            if(reportDigitalPin[pin = 3 + (6 * port)])
              value |= (digitalRead(pin) << 1);
            if(reportDigitalPin[pin = 4 + (6 * port)])
              value |= (digitalRead(pin) << 2);
            if(reportDigitalPin[pin = 5 + (6 * port)])
              value |= (digitalRead(pin) << 3);
            if(reportDigitalPin[pin = 6 + (6 * port)])
              value |= (digitalRead(pin) << 4);
            if(reportDigitalPin[pin = 7 + (6 * port)])
              value |= (digitalRead(pin) << 5);

            Serial.print(AS_ARGUMENT(value), BYTE);

        }
    }
}

void sendAnalogValues()
{
    for(int pin = 0; pin < 6; pin++)
    {
        if(reportAnalogPin[pin])
        {
            Serial.print(AS_COMMAND(RS_ANALOG_PIN), BYTE);            
            Serial.print(AS_ARGUMENT(pin), BYTE);
                        
            int value = analogRead(pin);
            byte value1 = value & 127;
            byte value2 = value >> 7;
            Serial.print(AS_ARGUMENT(value1), BYTE);            
            Serial.print(AS_ARGUMENT(value2), BYTE);

        }
    }
}
