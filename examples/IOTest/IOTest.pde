/**********************************************************************************************************************
 *Used with schematic http://www.digikey.com/schemeit/#eeu - sidenote: mpide doesn't like #'s in hyperlinks
 *PCF8574 with two buttons connected to pins 5&6, two red leds connected to pins 11&12 and two yellow leds connected to pins 9&10.
 *A0, A1, and A2 connected to ground to make the address 56.
 *I2C communication with SDA pin 15 connected to pin 20 on chipKit and SCL pin 14 connected to pin 21 on chipKit.
 *"Interupt" on PCF8574 pin 13 to pin 8 on chipKit
 *********************************************************************************************************************/

#include <libIO.h>
#include <Wire.h>
#include <inttypes.h>

libIO testIO(56); //device addressed to 56

bool LED1On = false;
bool LED2On = false;
char LED1 = 7; //P7 output on device
char LED2 = 6; //P6 output on device
char button1 = 0; //P0 input on device
char button2 = 1; //P1 input on device
int IO_Int = 8; //"Interupt" on pin 8 of chipKit
int IO_intState = HIGH; //device pulls low when input register changes

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting Sketch");
  Wire.begin();
  testIO.allOn(); //all outputs must be high prior to being used at inputs
  pinMode(IO_Int, INPUT);
  testIO.setOutOff(LED1);
  testIO.setOutOff(LED2);
}

void loop()
{  
  IO_intState = digitalRead(IO_Int);
  if (IO_intState == LOW)
  {
    if ((testIO.bitStat(button1)) && (!LED1On))  //use bitStat method with updating input register
    {
      testIO.setOutOn(LED1);
      LED1On = true;
      Serial.println("LED 1 On");
    }
    //use bitStat method without updating in input register 
    //should only be done after a bitStat that updates the input register
    else if ((testIO.bitStat(button1, false)) && (LED1On))  
    {
      testIO.setOutOff(LED1);
      LED1On = false;
      Serial.println("LED 1 Off");
    }
    if ((testIO.bitStat(button2, true)) && (!LED2On))  //bitStat method with updating input register
    {
      testIO.setOutOn(LED2);
      LED2On = true;
      Serial.println("LED 2 On");
    }
    else if ((testIO.bitStat(button2)) && (LED2On))  //use bitStat method with updating input register
    {
      testIO.setOutOff(LED2);
      LED2On = false;
      Serial.println("LED 2 Off");
    }
  } 
  delay(100); //delay for button pressing
}


