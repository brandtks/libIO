/*
	NOT TESTED!!
	libDAC - An I2C Extended IO Library for chipKit.
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
#include <Wire.h>
#include <libIO.h>
#include <WProgram.h>

/******************************************************************************
 * Class Variables
 ******************************************************************************/
int libIO::address = 0;
uint8_t libIO::outReg = 0;
boolean libIO::out[8] = {false, false, false, false, false, false, false, false};

/******************************************************************************
 * Constructors
 ******************************************************************************/
libIO::libIO(int initAddress)
{
	address = initAddress;
}

/******************************************************************************
 * Global Functions
 ******************************************************************************/

/**********************************************************
 *setup the device
 **********************************************************/
void libIO::init(char inOut)
{
	if (inOut == 1)
	{
		Wire.beginTransmission(address);
		Wire.send(0xFF);
		Wire.endTransmission();
	}
	else
	{
		Wire.beginTransmission(address);
		Wire.send(0x00);
		Wire.endTransmission();
	}
}

/**********************************************************
 *turn single bit output on
 **********************************************************/
void libIO::setOutOn(char bit)
{
	//add binary bit to byte being sent
	switch(bit)
	{
		case 0:
			outReg += 1;
			out[0] = true;
			break;
		case 1:
			outReg += 2;
			out[1] = true;
			break;
		case 2:
			outReg += 4;
			out[2] = true;
			break;
		case 3:
			outReg += 8;
			out[3] = true;
			break;
		case 4:
			outReg += 16;
			out[4] = true;
			break;
		case 5:
			outReg += 32;
			out[5] = true;
			break;
		case 6:
			outReg += 64;
			out[6] = true;
			break;
		case 7:
			outReg += 128;
			out[7] = true;
			break;
		default:
			break;
	}

	//send byte
	Wire.beginTransmission(address);
	Wire.send(outReg);
	Wire.endTransmission();
}

/**********************************************************
 *turn single bit output off
 **********************************************************/
void libIO::setOutOff(char bit)
{
	//subtract binary bit from byte being sent
	switch(bit)
	{
		case 0:
			if (out[0])
			{
				outReg -= 1;
				out[0] = false;
			}
			break;
		case 1:
			if (out[1])
			{
				outReg -= 2;
				out[1] = false;
			}
			break;
		case 2:
			if (out[2])
			{
				outReg -= 4;
				out[2] = false;
			}
			break;
		case 3:
			if (out[3])
			{
				outReg -= 8;
				out[3] = false;
			}
			break;
		case 4:
			if (out[4])
			{
				outReg -= 16;
				out[4] = false;
			}
			break;
		case 5:
			if (out[5])
			{
				outReg -= 32;
				out[5] = false;
			}
			break;
		case 6:
			if (out[6])
			{
				outReg -= 64;
				out[6] = false;
			}
			break;
		case 7:
			if (out[7])
			{
				outReg -= 128;
				out[7] = false;
			}
			break;
		default:
			break;
	}

	//send byte
	Wire.beginTransmission(address);
	Wire.send(outReg);
	Wire.endTransmission();
}

/**********************************************************
 *turn all outputs off
 **********************************************************/
uint8_t libIO::allOff()
{
	Wire.beginTransmission(address);
	Wire.send(0x00);
	Wire.endTransmission();
}

/**********************************************************
 *check specific bit status
 **********************************************************/
boolean libIO::bitStat(char bit)
{
	uint8_t byte = inputReg();

	byte >>= bit;
	byte = byte & 0x01;
	if (byte == 0x01)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**********************************************************
 *read input register
 **********************************************************/
uint8_t libIO::inputReg()
{
	uint8_t byte = 0;

	Wire.requestFrom(address,1);
	while(Wire.available())
	{
		byte = Wire.receive();
	}

	return byte;
}

