libDAC - An I2C Extended I/O Library for chipKit.
  

1. Description and Supported Devices
2. Method Description
3. ChangeLog

1)
Written by Skyler Brandt.
Supported Devices: 
	Texas Instrurments PCF8574 over I2C serial communications.

2)
____**Class instance**  libIO example(address):
Address is the I2C address of the device
**Example**
	libIO example(56);

____init(uint8_t inOut):
inout - INPUT
	  or
	OUTPUT
Initializes the device to be used as on output device with 0 or input with 1.
Writes a LOW or HIGH to all the pins.
When the PCF8574 powers up it writes a HIGH to all pins.
To use the PCF8574 as an input it has to have a HIGH written to the output to reduce current inside the device.
Returns VOID.
**Example for output device**
	example.init(OUTPUT);
**Example for input device**
	example.init(INPUT);

____writeOut(uint8_t bit, uint8_t state):
state - HIGH
	 or
	LOW
Writes a HIGH or LOW to the pin corresponding with the "bit" arguement.
Returns VOID.
**Example**
	example.writeOut(5, LOW);

____allOff():
Writes a LOW to all pins.
Returns VOID.
**Example**
	example.allOff();

____allOn():
Writes a HIGH to all pins.
Returns VOID.
**Example**
	example.allOn();

____getWrittenOutStatus(uint8_t bit):
Returns a TRUE or FALSE saved boolean status of the output. True is HIGH, false is LOW.
**Example**
	bool is5On = example.getWrittenOutStatus(5);

____bitStat(uint8_t bit):
Receives the input register from the device and then shifts off the number of bits to get to the bit corresponding to the pin desired.
Then determines if bit is a 1 or 0 and Returns HIGH or LOW.
**Example**
	uint8_t state5 = example.bitStat(5);

____bitStat(uint8_t bit, bool update):
Depending on if the update is true or false the input register will update. Everything else is the same as previous bitStat.
Should only be used after a bitStat() that updates the input register or inputArray().
Used to minimize I2C comms
**Example**
	uint8_t state6 = example.bitStat(6, false);

____inputArray();
Returns a pointer to an array of uint8_t with HIGH or LOW of each of the inputs.
**Example for input P5 and P6**
	uint8_t* in = example.inputArray();
	if (in[5] == HIGH)
	{
		*do some stuff*
	}
	if (in[6] == LOW)
	{
		*do some other stuff*
	}
	

3)
May 29, 2013 - Initial Release
June 15, 2013 - Functions now use uint8_t variable HIGH or LOW instead of true and false to more closely mimic the IO on the chipKit itself.
	Fixed some major fails in the inputArray().
	Using writeOut for outputs instead of seperate functions for turning an output on or off.
	Updated the example for the new code.
July 10, 2013 - Fixed individually addressed instances of the class