/*
  libIO - An I2C Extended IO Library for chipKit.
  Texas Instrurments PCF8574 over I2C serial communications.

  Created by Skyler Brandt on May 2013 for chipKit.

	Copyright 2013 Skyler Brandt
	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/
*/

#include <inttypes.h>
#include <WProgram.h>
#include <Wire.h>
#include <libIO.h>

/******************************************************************************
 * Constructors
 ******************************************************************************/
libIO::libIO(int initAddress)
{
	initiate(initAddress);
}

libIO::libIO()
{
	initiate(-1);
}

/******************************************************************************
 * Global Functions
 ******************************************************************************/

/**********************************************************
 *set instance device address
 **********************************************************/ 
void libIO::setAddress(int initAddress)
{
	this->address = initAddress;
}
 
/**********************************************************
 *setup the device to use as an output (1) or input (0)
 **********************************************************/
void libIO::init(uint8_t inOut)
{
	//set up device to be used as an inputs
	//must write highs to all the outputs to minimize current
	if (inOut == INPUT)
	{
		allOn();
	}
	else if (inOut == OUTPUT)  //set up as output
	{
		allOff();
	}
	else
	{
		return;
	}
}

/**********************************************************
 *write either a low or high to a specfic bit
 **********************************************************/
void libIO::writeOut(uint8_t tBit, uint8_t state)
{
	//write a low (0)
	if (state == LOW)
	{
		setOutOff(tBit);
	}
	
	//write a high (1)
	else if (state == HIGH)
	{
		setOutOn(tBit);
	}
	else
	{
		return;
	}
}

/**********************************************************
 *turn all outputs off
 **********************************************************/
void libIO::allOff()
{
	this->outReg = 0x00;
	setIO(this->outReg);
}

/**********************************************************
 *turn all outputs on
 **********************************************************/
void libIO::allOn()
{
	this->outReg = 0xFF;
	setIO(this->outReg);
}

/**********************************************************
 *
 **********************************************************/
void libIO::outputMaskOn(uint8_t outputMask)
{
	this->outReg |= outputMask;
	setIO(this->outReg);
}

/**********************************************************
 *
 **********************************************************/
void libIO::outputMaskOff(uint8_t outputMask)
{
	this->outReg &= ~outputMask;
	setIO(this->outReg);
}


/**********************************************************
 *check specific bit status
 **********************************************************/
uint8_t libIO::bitStat(uint8_t tBit)
{
	uint8_t tByte = inputReg(); //get input register from device

	tByte >>= tBit;  //shift off bits
	tByte &= 0x01;  //determine if the first bit is a 1 or 0
	if (tByte == 0x01)
	{
		return HIGH;
	}
	else
	{
		return LOW;
	}
}

/**********************************************************
 *returns pointer to an array of HIGH/LOW on the status of the input register
 **********************************************************/
uint8_t* libIO::inputArray()
{
	uint8_t* in = new uint8_t[8];
	uint8_t tempByte = 0;
  
	uint8_t tByte = inputReg(); //get input register from device

	for (uint8_t i=0 ; i<8 ; i++)
	{
		tempByte = tByte;
		tempByte >>= i;
		tempByte &= 0x01;
		if (tempByte == 0x01)
		{
			in[i] = HIGH;
		}
		else
		{
			in[i] = LOW;
		}
	}
	return in;
}

/******************************************************************************
 *Private Functions
 ******************************************************************************/

 /**********************************************************
 *initiate
 **********************************************************/
void libIO::initiate(int initAddress)
{
	this->address = initAddress;  //address of the device
	this->outReg = 0xFF;
}

/**********************************************************
 *turn single bit output on
 **********************************************************/
void libIO::setOutOn(uint8_t tBit)
{
	uint8_t tByte = powerTwo(tBit);  //convert integer to BCD
	this->outReg |= tByte;
	setIO(this->outReg);
}

/**********************************************************
 *turn single bit output off
 **********************************************************/
void libIO::setOutOff(uint8_t tBit)
{
	uint_t tByte = powerTwo(tBit); //convert integer to BCD
	this->outReg &= ~tByte;
	setIO(this->outReg);  //send output register
}

/**********************************************************
 *send output Registers via I2C to device
 **********************************************************/
void libIO::setIO(uint8_t outputRegister)
{
	uint8_t sendByte[2] = {0, outputRegister};
	Wire.beginTransmission(this->address);
	Wire.send(sendByte, 2);
	Wire.endTransmission();
}

/**********************************************************
 *read input register
 **********************************************************/
uint8_t libIO::inputReg()
{
	uint8_t registerByte = 0;
	Wire.requestFrom(this->address,2);
	while(Wire.available())
	{
		registerByte = Wire.receive();
		registerByte = Wire.receive();
	}

	return registerByte;
}

/**********************************************************
 *Power of Two Calculation
 **********************************************************/
uint8_t libIO::powerTwo(double n)
{
	return pow(2, n);
}