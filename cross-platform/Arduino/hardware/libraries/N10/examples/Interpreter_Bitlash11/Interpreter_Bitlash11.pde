#include "BrainM644.h"




//##
//////////////////////////////////////////////////////////////////
//
//	userfunctions.pde:	Bitlash User Functions Demo Code
//
//	Copyright 2010 by Bill Roy
//
//	Permission is hereby granted, free of charge, to any person
//	obtaining a copy of this software and associated documentation
//	files (the "Software"), to deal in the Software without
//	restriction, including without limitation the rights to use,
//	copy, modify, merge, publish, distribute, sublicense, and/or sell
//	copies of the Software, and to permit persons to whom the
//	Software is furnished to do so, subject to the following
//	conditions:
//	
//	The above copyright notice and this permission notice shall be
//	included in all copies or substantial portions of the Software.
//	
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
//	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//	OTHER DEALINGS IN THE SOFTWARE.
//
//////////////////////////////////////////////////////////////////
//

//##

//#include "WProgram.h"
#include "bitlash.h"

// Declare a user function named "timer1" returning a numeric Bitlash value
//
void motor0_setSpeed(numvar speed)
{ 
  motor0.setSpeed(speed);
}

void motor1_setSpeed(numvar speed)
{ 
  motor1.setSpeed(speed);
}

numvar motor0_getSpeed()
{
  return motor0.getSpeed();
}

numvar motor1_getSpeed()
{
  return motor1.getSpeed();
}

void motor0_brake()
{
  motor0.brake();
}

void motor1_brake()
{
  motor1.brake();
}


void setup(void) 
{
  /* ##Pendientes:
    - Documentar.
    - Control de LEDs de usuarios.
    - Lectura de pulsador.
    - Lectura de Ranger Sharp (¿en entradas analógicas, tipo función "ranger(0)" ).
    - Encoders.
      - Ver: http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1185064568
    - Lectura de PNA
    - PID
    - Navegación diferencial
    
    - Ejemplos bitlash:
      - Seguidor de línea
      - etc..
  */
  
  initBitlash(115200);		// must be first to initialize serial port
  
  //Multiplo.N10:
  motor0.setClockwise(false);
  
  // Register the extension function with Bitlash
  //		"timer1" is the Bitlash name for the function
  //		0 is the argument signature: takes 0 arguments
  //		(bitlash_function) timer1 tells Bitlash where our handler lives
  //
  addBitlashFunction("mot0", -1, (bitlash_function) motor0_setSpeed);
  addBitlashFunction("mot1", -1, (bitlash_function) motor1_setSpeed);
  addBitlashFunction("brake0", 0, (bitlash_function) motor0_brake);
  addBitlashFunction("brake1", 0, (bitlash_function) motor1_brake);
  //addBitlashFunction("getmot0", 0, (bitlash_function) motor0_getSpeed);
  //addBitlashFunction("getmot1", 0, (bitlash_function) motor1_getSpeed);
}

void loop(void) {
	runBitlash();
}