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

#ifndef LIB_IO_H
#define LIB_IO_H

#include <inttypes.h>

class libIO
{
	private:

	public:
		void init(char inOut);
		void setOutOn(char bit);
		void setOutOff(char bit);
		void allOff();
		boolean bitStat(char bit);
		uint8_t inputReg();
};

#endif
