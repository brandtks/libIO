libDAC - An I2C Extended I/O Library for chipKit.
  

1. Description and Supported Devices
2. Method Description
3. ChangeLog

1)
Written by Skyler Brandt.
Supported Devices: 
	Texas Instrurments PCF8574 over I2C serial communications.

2)
**Class instance**  libIO example(address):
	Address is the I2C address of the device
	**Example**
		libIO example(56);

init(char inOut):
	Initializes the device to be used as on output device with 0 or input with 1.
	Writes a LOW or HIGH to all the pins.
	When the PCF8574 powers up it writes a HIGH to all pins.
	To use the PCF8574 as an input it has to have a HIGH written to the output to reduce current inside the device.
	Returns VOID.
	**Example for output device**
		example.init(0);
	**Example for input device**
		example.init(1);

setOutOn(char bit):
	Writes a HIGH to the pin corresponding with the "bit" arguement.
	Returns VOID.
	**Example**
		example.setOutOn(5);

setOutOff(char bit):
	Writes a LOW to the pin corresponding with the "bit" arguement.
	Returns VOID.
	**Example**
		example.setOutOff(5);

allOff():
	Writes a LOW to all pins.
	Returns VOID.
	**Example**
		example.allOff();

allOn():
	Writes a HIGH to all pins.
	Returns VOID.
	**Example**
		example.allOn();

bitStat(char bit):
	Receives the input register from the device and then shifts off the number of bits to get to the bit corresponding to the pin desired.
	Then determines if bit is a 1 or 0 and Returns TRUE OR FALSE.
	**Example**
		bool exampleP5On = example.bitStat(5);

bitStat(char bit, bool update):
	Depending on if the update is true or false the input register will update. Everything else is the same as previous bitStat.
	Should only be used after a bitStat that updates the input register. 
	Used to minimize I2C comms
	**Example**
		bool exampleP6On = example.bitStat(6, false);

inputArray();
	Returns a pointer to an array of bool with the true or false of each of the pins.
	****************************************************************
	**Can only be called for a device used exclusively for inputs.**
	****************************************************************
	**Example for input P5 and P6**
		bool *in;
		in = example.inputArray();
		if (in + 5)
		{
			*do some stuff*
		}
		if (in +6)
		{
			*do some other stuff*
		}
	
3)
Initial Release - May 29, 2013