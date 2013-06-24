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

#ifndef LIB_IO_H
#define LIB_IO_H

#include <inttypes.h>

#define HIGH 1
#define LOW 0

#define INPUT 0
#define OUTPUT 1

class libIO
{
private:
  int address;
  uint8_t outReg;
  bool out[8];
  uint8_t inReg;
  
	void setOutOn(uint8_t bit);
  void setOutOff(uint8_t bit);  
	void setIO(uint8_t outputReg);
  uint8_t inputReg();

public:
  libIO(int initAddress);
  void init(uint8_t inOut);
	void writeOut(uint8_t bit, uint8_t state);
  void allOff();
  void allOn();
	bool getWrittenOutStatus(uint8_t bit);
  uint8_t bitStat(uint8_t bit);
  uint8_t bitStat(uint8_t bit, bool update);
  uint8_t* inputArray();
};

#endif

