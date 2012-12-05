//////////////////////////////////////////////////////////////////
//
//	tone.pde:	Bitlash tone User Function Code
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
#include "WProgram.h"
#include "bitlash.h"

// function handler for "tone()" bitlash function
//
void tone_func(numvar pin, numvar freq, numvar duration) {
	tone(pin, freq, duration);
	// delay(duration); 	// uncomment this line if you want tone() to be blocking
}


void setup(void) {
	initBitlash(57600);		// must be first to initialize serial port

	// Register the extension function with Bitlash:
	// 		"tone" is the name Bitlash will match for the function
	// 		3 is the argument signature: 3 args, <0 means returns no value
	// 		(bitlash_function) tone_func is the C function handler declared above
	//
	addBitlashFunction("tone", -3, (bitlash_function) tone_func);
}

void loop(void) {
	runBitlash();
}
