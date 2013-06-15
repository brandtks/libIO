/*
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
  static int address;
  static uint8_t outReg;
  static bool out[8];
  static uint8_t inReg;
  static void setIO(uint8_t outputReg);
  static uint8_t inputReg();

public:
  libIO(int initAddress);
  void init(uint8_t inOut);
  void setOutOn(uint8_t bit);
  void setOutOff(uint8_t bit);
  void allOff();
  void allOn();
  bool bitStat(uint8_t bit);
  bool bitStat(uint8_t bit, bool update);
  bool* inputArray();
};

#endif

