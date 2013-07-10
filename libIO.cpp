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
}

/**********************************************************
 *write either a low or high to a specfic bit
 **********************************************************/
void libIO::writeOut(uint8_t bit, uint8_t state)
{
	//write a low (0)
	if (state == LOW)
	{
		setOutOff(bit);
	}
	//write a high (1)
	else if (state == HIGH)
	{
		setOutOn(bit);
	}
}

/**********************************************************
 *turn all outputs off
 **********************************************************/
void libIO::allOff()
{
	outReg = 0x00;
	setIO(outReg);
	for (uint8_t i=0 ; i<8 ; i++)
	{
		this->out[i] = false;
	}
}

/**********************************************************
 *turn all outputs on
 **********************************************************/
void libIO::allOn()
{
	outReg = 0xFF;
	setIO(outReg);
	for (uint8_t i=0 ; i<8 ; i++)
	{
		this->out[i] = true;
	}
}

/**********************************************************
 *get the saved bool status of the output
 **********************************************************/
bool libIO::getWrittenOutStatus(uint8_t bit)
{
	return this->out[bit];
}

/**********************************************************
 *check specific bit status
 **********************************************************/
//gets input register from device
uint8_t libIO::bitStat(uint8_t bit)
{
	uint8_t inByte = inputReg(); //get input register from device
	this->inReg = inByte;  //save to class variable
	inByte >>= bit;  //shift off bits
	inByte = inByte & 0x01;  //determine if the first bit is a 1 or 0
	if (inByte == 0x01)
	{
		return HIGH;
	}
	else
	{
		return LOW;
	}
}

uint8_t libIO::bitStat(uint8_t bit, bool update)
{
	uint8_t byte = 0;

	if (update)
	{
		byte = inputReg();  //get input register from device
		this->inReg = byte;  //save to class variable
	}
	else
	{
		byte = this->inReg;  //used if already updated input register on that scan and want to check the status of another bit
	}
	byte >>= bit;  //shift off bits
	byte = byte & 0x01;
	if (byte == 0x01)
	{
		return HIGH;
	}
	else
	{
		return LOW;
	}
}

/**********************************************************
 *returns pointer to an array of booleans on the status of the input byte
 **********************************************************/
uint8_t* libIO::inputArray()
{
	uint8_t* in = new uint8_t[8];
	uint8_t tempByte = 0;
  
	uint8_t byte = inputReg(); //get input register from device
	this->inReg = byte;  //save input register to class variable

	for (uint8_t i=0 ; i<8 ; i++)
	{
		tempByte = byte;
		tempByte >>= i;
		tempByte = tempByte & 0x01;
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
	for (uint8_t i=0 ; i<8 ; i++)
	{
		this->out[i] = true;
	}
}
 
/**********************************************************
 *turn single bit output on
 **********************************************************/
void libIO::setOutOn(uint8_t bit)
{
	//add binary bit to byte being sent
	if (!this->out[bit])
	{
		this->outReg += powerTwo(bit);
		this->out[bit] = true;
	}
	
	/*
	switch(bit)
	{
	case 0:
		if (!this->out[0])
		{
			this->outReg += 1;
			this->out[0] = true;
		}
		break;
	case 1:
		if (!this->out[1])
		{
			this->outReg += 2;
			this->out[1] = true;
		}
		break;
	case 2:
		if (!this->out[2])
		{
			this->outReg += 4;
			this->out[2] = true;
		}
		break;
	case 3:
		if (!this->out[3])
		{
			this->outReg += 8;
			this->out[3] = true;
		}
		break;
	case 4:
		if (!this->out[4])
		{
			this->outReg += 16;
			this->out[4] = true;
		}
		break;
	case 5:
		if (!this->out[5])
		{
			this->outReg += 32;
			this->out[5] = true;
		}
		break;
	case 6:
		if (!this->out[6])
		{
			this->outReg += 64;
			this->out[6] = true;
		}
		break;
	case 7:
		if (!this->out[7])
		{
			this->outReg += 128;
			this->out[7] = true;
		}
		break;
	default:
		break;
	}
	*/
	
	//send byte
	setIO(this->outReg);
}

/**********************************************************
 *turn single bit output off
 **********************************************************/
void libIO::setOutOff(uint8_t bit)
{
	//subtract binary bit from byte being sent
	if (this->out[bit])
	{
		this->outReg -= powerTwo(bit);
		this->out[bit] = false;
	}

	/*
	switch(bit)
	{
	case 0:
		if (this->out[0])
		{
			this->outReg -= 1;
			this->out[0] = false;
		}
		break;
	case 1:
		if (this->out[1])
		{
			this->outReg -= 2;
			this->out[1] = false;
		}
		break;
	case 2:
		if (this->out[2])
		{
			this->outReg -= 4;
			this->out[2] = false;
		}
		break;
	case 3:
		if (this->out[3])
		{
			this->outReg -= 8;
			this->out[3] = false;
		}
		break;
	case 4:
		if (this->out[4])
		{
			this->outReg -= 16;
			this->out[4] = false;
		}
		break;
	case 5:
		if (this->out[5])
		{
			this->outReg -= 32;
			this->out[5] = false;
		}
		break;
	case 6:
		if (this->out[6])
		{
			this->outReg -= 64;
			this->out[6] = false;
		}
		break;
	case 7:
		if (this->out[7])
		{
			this->outReg -= 128;
			this->out[7] = false;
		}
		break;
	default:
		break;
	}
	*/

	//send byte
	setIO(this->outReg);
}

/**********************************************************
 *send output Registers via I2C to device
 **********************************************************/
void libIO::setIO(uint8_t outputReg)
{
	uint8_t sendByte[2] = {0, outputReg};
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