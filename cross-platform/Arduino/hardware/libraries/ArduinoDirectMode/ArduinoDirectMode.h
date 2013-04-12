#include "QueueArray.h"
#include "WString.cpp" //Why do I need to include this?!? #Richo
#include "Servo.cpp"
#include "Tone.cpp"

/* REQUEST COMMANDS */
#define RQ_ACTIVATE_ANALOG_PIN                         0
#define RQ_ANALOG_WRITE                                1
#define RQ_ACTIVATE_DIGITAL_PORT                       2
#define RQ_DIGITAL_PIN_MODE                            3
#define RQ_DIGITAL_WRITE                               4
#define RQ_ATTACH_SERVO                                5
#define RQ_SERVO_ANGLE                                 6
#define RQ_DETACH_SERVO                                7
#define RQ_DISCONNECT								   8
#define RQ_PLAY_TONE								   9
/* ... gap to avoid collisions with DuinoBot ... */
#define RQ_AF_DCMOTOR							  	  13


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
#define SERVO(x)                     (myservos[(x) - 2]) // 2 to 19
#define AF_DCMOTOR(x)                (mymotors[(x) - 1]) // 1 to 4


extern "C" void __cxa_pure_virtual() {} //Why do I need to include this?!? #Richo


bool reportAnalogPin[6] = {false, false, false, false, false, false};
bool reportDigitalPort[2] = {false, false};
bool reportDigitalPin[12] = {false, false, false, false, false, false, false, false, false, false, false, false};
Servo myservos[12];

long previousMillis = 0; 
long interval = 15;


int argsToRead = -1;
QueueArray <byte> queue;

//AF_DCMotor mymotors[4];


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
void executeDisconnect();
void executePlayTone();
void executeAFDCMotor();

/******************* SHIFT REGISTER BEGIN *****************/

/* shift register related stuff */
/* TODO:
 * - implement run & setSpeed on the PC side
 *   => check AFMotor.cpp/.h
 * - remember which motor is where
 *   => use this information
 *  (order of bits in the shift reg)
 *      #define MOTOR1_A 2
 *      #define MOTOR1_B 3
 *      #define MOTOR2_A 1
 *      #define MOTOR2_B 4
 *      #define MOTOR4_A 0
 *      #define MOTOR4_B 6
 *      #define MOTOR3_A 5
 *      #define MOTOR3_B 7
 * - add capabilities on related pins ?
 * - reserve pins used for the shift register & pwm:
 *   => cf #defines below
 *   => cf PWM info below
 * - Check these info:
 *   => PWM1 is on arduino (uno) pin #11
 *   => PWM2 is on arduino (uno) pin #3
 *   => PWM3 is on arduino (uno) pin #6
 *   => PWM4 is on arduino (uno) pin #5
 * - send data on a sysex request, ID: SHIFT_DATA 0x75
 *   => use first version of the firmata proposal
 */
 #define PWM1 11
 #define PWM2 3
 #define PWM3 6
 #define PWM4 5

 #define MOTOR1_A 2
 #define MOTOR1_B 3
 #define MOTOR2_A 1
 #define MOTOR2_B 4
 #define MOTOR4_A 0
 #define MOTOR4_B 6
 #define MOTOR3_A 5
 #define MOTOR3_B 7
 
//TODO: should be configured instead of hardcoded
#define MOTORLATCH 12
#define MOTORCLK 4
#define MOTORENABLE 7
#define MOTORDATA 8

#define FORWARD 1
#define BACKWARD 2
#define RELEASE 3

#define MOTOR12_64KHZ _BV(CS20)  // no prescale
#define MOTOR12_8KHZ _BV(CS21)   // divide by 8
#define MOTOR12_2KHZ _BV(CS21) | _BV(CS20) // divide by 32
#define MOTOR12_1KHZ _BV(CS22)  // divide by 64

#define MOTOR34_64KHZ _BV(CS00)  // no prescale
#define MOTOR34_8KHZ _BV(CS01)   // divide by 8
#define MOTOR34_1KHZ _BV(CS01) | _BV(CS00)  // divide by 64

//TODO: #define SHIFTREG as a pinmode possibility => nope, it already exists as 'SHIFT' (should be thought about, tho).

void shiftRegister_enable(void);
void shiftRegister_tx(void);

static uint8_t latch_state;

/*==============================================================================
 * FUNCTIONS
 *============================================================================*/
inline void initPWM1(uint8_t freq) {
    // use PWM from timer2A on PB3 (Arduino pin #11)
    TCCR2A |= _BV(COM2A1) | _BV(WGM20) | _BV(WGM21); // fast PWM, turn on oc2a
    TCCR2B = freq & 0x7;
    OCR2A = 0;
    pinMode(11, OUTPUT);
}

inline void setPWM1(uint8_t s) {
    // use PWM from timer2A on PB3 (Arduino pin #11)
    OCR2A = s;
}

inline void initPWM2(uint8_t freq) {
    // use PWM from timer2B (pin 3)
    TCCR2A |= _BV(COM2B1) | _BV(WGM20) | _BV(WGM21); // fast PWM, turn on oc2b
    TCCR2B = freq & 0x7;
    OCR2B = 0;
    pinMode(3, OUTPUT);
}

inline void setPWM2(uint8_t s) {
    // use PWM from timer2A on PB3 (Arduino pin #11)
    OCR2B = s;
}

inline void initPWM3(uint8_t freq) {
    // use PWM from timer0A / PD6 (pin 6)
    TCCR0A |= _BV(COM0A1) | _BV(WGM00) | _BV(WGM01); // fast PWM, turn on OC0A
    //TCCR0B = freq & 0x7;
    OCR0A = 0;
    pinMode(6, OUTPUT);
}

inline void setPWM3(uint8_t s) {
    // use PWM from timer0A on PB3 (Arduino pin #6)
    OCR0A = s;
}

inline void initPWM4(uint8_t freq) {
    // use PWM from timer0B / PD5 (pin 5)
    TCCR0A |= _BV(COM0B1) | _BV(WGM00) | _BV(WGM01); // fast PWM, turn on oc0a
    //TCCR0B = freq & 0x7;
    OCR0B = 0;
    pinMode(5, OUTPUT);
}

inline void setPWM4(uint8_t s) {
    // use PWM from timer0A on PB3 (Arduino pin #6)
    OCR0B = s;
}

void motorRun(uint8_t motornum, uint8_t cmd, uint8_t pwmSpeed) {
  uint8_t a, b;
  switch (motornum) {
    case 1:
      a = MOTOR1_A; b = MOTOR1_B;setPWM1(pwmSpeed);break;
    case 2:
      a = MOTOR2_A; b = MOTOR2_B;setPWM2(pwmSpeed);break;
    case 3:
      a = MOTOR3_A; b = MOTOR3_B;setPWM3(pwmSpeed);break;
    case 4:
      a = MOTOR4_A; b = MOTOR4_B;setPWM4(pwmSpeed);break;
    default:
      return;
  }
  
  switch (cmd) {
    case FORWARD:
      latch_state |= _BV(a);
      latch_state &= ~_BV(b); 
      shiftRegister_tx();
      break;
    case BACKWARD:
      latch_state &= ~_BV(a);
      latch_state |= _BV(b); 
      shiftRegister_tx();
      break;
    case RELEASE:
      latch_state &= ~_BV(a);
      latch_state &= ~_BV(b); 
      shiftRegister_tx();
      break;
  }



}
  
//TODO: rewrite this completely
void shiftRegister_enable() {
 // setup the latch
 pinMode(MOTORLATCH, OUTPUT);
 pinMode(MOTORENABLE, OUTPUT);
 pinMode(MOTORDATA, OUTPUT);
 pinMode(MOTORCLK, OUTPUT);

 latch_state = 0;

 shiftRegister_tx();  // "reset"

 //ENABLE_PORT &= ~_BV(ENABLE); // enable the chip outputs!
 digitalWrite(MOTORENABLE, LOW);
 
 initPWM1(MOTOR12_64KHZ);
 initPWM2(MOTOR12_64KHZ);
 initPWM3(MOTOR34_64KHZ);
 initPWM4(MOTOR34_64KHZ);
}


//use this function to send shift reg data
void shiftRegister_tx(void) {
  uint8_t i;

  //LATCH_PORT &= ~_BV(LATCH);
  digitalWrite(MOTORLATCH, LOW);

  //SER_PORT &= ~_BV(SER);
  digitalWrite(MOTORDATA, LOW);

  for (i=0; i<8; i++) {
    //CLK_PORT &= ~_BV(CLK);
    digitalWrite(MOTORCLK, LOW);

    if (latch_state & _BV(7-i)) {
      //SER_PORT |= _BV(SER);
      digitalWrite(MOTORDATA, HIGH);
    } else {
      //SER_PORT &= ~_BV(SER);
      digitalWrite(MOTORDATA, LOW);
    }
    //CLK_PORT |= _BV(CLK);
    digitalWrite(MOTORCLK, HIGH);
  }
  //LATCH_PORT |= _BV(LATCH);
  digitalWrite(MOTORLATCH, HIGH);
  
  //PWM 100%
//  digitalWrite(PWM1, HIGH);
//  digitalWrite(PWM2, HIGH);
//  digitalWrite(PWM3, HIGH);
//  digitalWrite(PWM4, HIGH);
}

/*************** SHIFT REGISTER END **************/

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
		case RQ_PLAY_TONE:
			argsToRead = 6;
			break;
		case RQ_AF_DCMOTOR:
			argsToRead = 4;
			break;
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
		case RQ_DISCONNECT:
			argsToRead = 0;
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
		case RQ_DISCONNECT:
			executeDisconnect();
			break;
		case RQ_PLAY_TONE:
			executePlayTone();
			break;
		case RQ_AF_DCMOTOR:
			executeAFDCMotor();
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

void executeDisconnect()
{
	establishContact();
}

void executePlayTone()
{
	byte pin = queue.pop();
	unsigned int freq;
	unsigned long dur;
	
	//frequency
	freq = queue.pop();
	freq |= (queue.pop() << 7);
	freq |= (queue.pop() << 14);
	//duration
	dur = queue.pop();
	dur |= (queue.pop() << 7);
	
	tone(pin, freq, dur);	
}

void executeAFDCMotor()
{
    byte motor = queue.pop();
    byte cmd = queue.pop();	
	byte value1 = queue.pop();
    byte value2 = queue.pop();
    byte speed = value1 | (value2 << 7);
	
	shiftRegister_enable();  //shouldnt do that this way (inefficient), but...
     
     //latch_state = 0x00;//clear old state
     
     //argv[0] byte 2 de la desc : datapin
     //argv[1] byte 3 de la desc : clockpin
     //argv[2] byte 4 de la desc : latchpin
     //argv[3] byte 5 de la desc : msbfirst (boolean)
     //argv[4] byte 6 de la desc : bits 0-6
     //argv[5] byte 7 de la desc : bit 7
     
     //latch_state |= (argv[4]&0x7F);//grab new data: bits 0-6 at pos 0..6
     //latch_state |= (((argv[5]&0x7F)<<7) & 0x80);//grab new data: bit 7 is at pos 0
     //shiftRegister_tx();//output that data
     //no output on serial
     
     motorRun(motor, cmd, speed);
    /*
	AF_DCMOTOR(motor).init(motor);
	AF_DCMOTOR(motor).setSpeed(speed);
	AF_DCMOTOR(motor).run(cmd);
	*/
	/*
	// ECHO
	Serial.print(AS_COMMAND(RQ_AF_DCMOTOR), BYTE);
	Serial.print(AS_ARGUMENT(motor), BYTE);
	Serial.print(AS_ARGUMENT(cmd), BYTE);
	Serial.print(AS_ARGUMENT(value1), BYTE);
	Serial.print(AS_ARGUMENT(value2), BYTE);
	*/
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
