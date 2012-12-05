#ifndef MotorDC__h
#define MotorDC__h

/* 	MotorDC

	A small DC motor control class.

	Copyright (C) 2010 Multiplo
	http://robotgroup.com.ar
	http://multiplo.org
	Created by Julián U. da Silva Gillig.

	IMPORTANT NOTICE: This library is based on code from the SNAPI library, which is under The Multiplo Pacifist
	License. This license is not compatible with the GNU Lesser General Public License (LGPL), so this library (the
	MotorDC	library) has an special	written exception from Multiplo, and is deployed under the LGPL, in order to be
	compiled with the Arduino libraries and other LGPL libraries. But this does not	affects the SNAPI original license
	in any way, and DOES NOT AUTHORIZES ANY THIRD PARTY TO USE OR REDISTRIBUTE THE SNAPI LIBRARY UNDER THE LGPL. In
	other words: This exception ONLY AFFECTS the Arduino version of the DCMotor library.

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	NOTE: We strongly believe in peace, so we would not like to see our work in any non-civil or military project.
	But, due to the Arduino's GPL license which we do have to maintain, this is only a recommendation and an
	expression of our wishes.
*/

#include "WProgram.h"


#define MAX_SPEED 100.0
#define MIN_SPEED (-MAX_SPEED)


class MotorDC
{
	private:
		bool clockwise, braked;
		float speed, prevSpeed;
		int enable_pin, d0_pin, d1_pin;


	public:
		MotorDC(const int enable_pin,
				const int d0_pin, const int d1_pin,
				const bool clockwise = true) 		:	clockwise(clockwise),
														braked(false),
														speed(0.0), prevSpeed(0.0),
														enable_pin(enable_pin),
														d0_pin(d0_pin), d1_pin(d1_pin)
		{
			pinMode(enable_pin, OUTPUT);
			pinMode(d0_pin, OUTPUT);
			pinMode(d1_pin, OUTPUT);
			digitalWrite(enable_pin, LOW);
			digitalWrite(d0_pin, LOW);
			digitalWrite(d1_pin, LOW);
		}


		void setClockwise(const bool value)
		{
			clockwise = value;
			if (!braked)
				setSpeed(speed);
		}


		bool getClockwise() const
		{
			return clockwise;
		}


		void setSpeed(const float value)
		{
			float tempSpeed = constrain(value, MIN_SPEED, MAX_SPEED);

			prevSpeed = speed;
			speed = tempSpeed;

			if (!clockwise)
				tempSpeed = (-tempSpeed);

			if (tempSpeed > 0)
			{
				digitalWrite(d0_pin, LOW);
				digitalWrite(d1_pin, HIGH);
			}
			else
			{
				digitalWrite(d0_pin, HIGH);
				digitalWrite(d1_pin, LOW);
			}
			analogWrite( enable_pin, (int)(abs(tempSpeed/MAX_SPEED)*255) );
			braked = false;
		}


		float getSpeed() const
		{
			return speed;
		}


		float getPrevSpeed() const
		{
			return prevSpeed;
		}


		void brake()
		{
			digitalWrite(d0_pin, HIGH);
			digitalWrite(d1_pin, HIGH);
			analogWrite(enable_pin, 255);
			braked = true;
		}


		bool isBraked() const
		{
			return braked;
		}


		int version() const
		{
			return 1;
		}
};

#endif
