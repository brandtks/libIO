#include <libIO.h>
#include <Wire.h>
#include <inttypes.h>

libIO testIO(56);

#define LED1 6
#define LED2 7
#define button1 0
#define button2 1
#define INT 8

uint8_t stateLED1 = LOW;
uint8_t stateLED2 = LOW;

void setup()
{
  Serial.begin(9600);
  Serial.println("Sketch Start");
  Wire.begin();
  testIO.init(INPUT);
  pinMode(INT, INPUT);
  testIO.writeOut(LED1, stateLED1);
  testIO.writeOut(LED2, stateLED2);
}

void loop()
{
  uint8_t IOInt = digitalRead(INT);  //device sends an interrupt when an input changes state
  if (IOInt == LOW)  //an interrupt pulls low during a state change
  {
    Serial.println("Interrupt Received");
    uint8_t* inReg = testIO.inputArray();  //get the point to array of HIGH/LOW's for each input
    stateLED1 = inReg[button1];  //set LED 1 to button 1
    testIO.writeOut(LED1, stateLED1);  //write LED 1 output
    stateLED2 = testIO.bitStat(button2);  //get status of button 2 and set LED 2
    testIO.writeOut(LED2, stateLED2);
  }
}
