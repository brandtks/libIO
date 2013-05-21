/*
	NOT TESTED!!
	libIO - A I2C extended IO for Texas Instrurments PCF8574.

	Created by Skyler Brandt on May 2013 for chipKit.

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
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
