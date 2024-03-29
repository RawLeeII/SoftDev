/******************************************************************************
<SparkFun MPL3115A2 Simple Sketch>
<Dave @ SparkFun Electronics>
<November 2014>
<https://github.com/sparkfun/ITG-3200_Breakout>
*/

// PIR example
#include <Wire.h>
#include <SparkFunMPL3115A2.h>
#include <SoftwareSerial.h>

SoftwareSerial display(3, 2);

//Create an instance of the object
MPL3115A2 myPressure;

char pastring[10];
char tmpstring[10];

float pressure;
float temperature;

int ipress;
int itemp;

int LDR_Pin = A0;

void setup()
{
  Wire.begin();        // Join i2c bus
  Serial.begin(9600);  // Start serial for output

  myPressure.begin(); // Get sensor online

  myPressure.setModeBarometer(); // Measure pressure in Pascals from 20 to 110 kPa
  
  myPressure.setOversampleRate(7); // Set Oversample to the recommended 128
  myPressure.enableEventFlags(); // Enable all three pressure and temp event flags 

  display.begin(9600);
  Serial.begin(9600);
  delay(500);

  display.write(254); // move cursor to beginning of first line
  display.write(128);

  display.write("                "); // clear display
  display.write("                ");
}

void loop()
{
  pressure = myPressure.readPressure();
  ipress = pressure;
  sprintf(pastring, "%3d", ipress);

  Serial.print("Pressure(Pa): ");
  Serial.print(pastring);
  Serial.println();

  display.write("Pres (Pa): ");
  display.write(pastring);

  temperature = myPressure.readTempF();
  itemp = temperature;
  sprintf(tmpstring, "%3d", itemp);

  Serial.print("Temp(f): ");
  Serial.print(temperature, 2);
  Serial.println();

  display.write("Temp (f): ");
  display.write(tmpstring);

  

  display.write(254); // move cursor to beginning of first line
  display.write(128);
  int LDRReading = analogRead(LDR_Pin);

  Serial.print("LDR Reading: ");
  Serial.print(LDRReading);
  Serial.println();
  Serial.println();
  Serial.println();
  delay(250); //just here to slow down the output for easier reading
}