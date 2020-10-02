/*
 * I use this post as a Source: https://gist.github.com/ho2electronics/d3067448cadadc971439e621e6a8e0b4
 2 -> HX711 CLK
 3 -> DOUT
 5V -> VCC
 GND -> GND
*/

#include "HX711.h"  // you can download it from https://github.com/juano2310/HX711ADC
#include <SoftwareSerial.h>//This library allow us to use additional pins for a new serial interface
int rxPin = 10;//NODEMCU RX pin
int txPin = 11;//NODEMCU TX pin
SoftwareSerial esp(rxPin, txPin);//We call software serial as esp and we set rx&tx pins
#define DOUT  3//Data Out pin from HX711 Module
#define CLK  2//CLOCK SIGNAL pin
int i=0;// we use this variable as a counter for taking average load value
float temp=0;// we use this variable as a temporary sum for taking average load value
HX711 scale(DOUT, CLK);//we set HX711 pins

//Change this calibration factor as per your load cell once it is found you many need to vary it in thousands
float calibration_factor = -381650; //It depends on your loadcell type

//=============================================================================================
//                         SETUP
//=============================================================================================
void setup() {
  
  Serial.begin(9600);
  esp.begin(9600);
  Serial.println("HX711 Calibration");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press a,s,d,f to increase calibration factor by 10,100,1000,10000 respectively");
  Serial.println("Press z,x,c,v to decrease calibration factor by 10,100,1000,10000 respectively");
  Serial.println("Press t for tare");
  scale.set_scale();
  scale.tare(); //Reset the scale to 0

  long zero_factor = scale.read_average(); //Get a baseline reading
  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);
}

//=============================================================================================
//                         LOOP
//=============================================================================================
void loop() {

  scale.set_scale(calibration_factor); //Adjust to this calibration factor
i++;
  Serial.print("Reading: ");
  Serial.print(scale.get_units(), 3);
  Serial.print(" kg"); //Change this to kg and re-adjust the calibration factor if you follow SI units like a sane person
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();
  
  temp+=scale.get_units();
  if(i>=10){
   esp.println((temp/i),3);//send average value to NODEMCU
   i=0;//make counter zero
   temp=0;/make temp variable zero
  Serial.print("Reading: ");
  Serial.print(scale.get_units(), 3);
  Serial.print(" kg"); //Change this to kg and re-adjust the calibration factor if you follow SI units like a sane person
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();
  }
  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      calibration_factor += 10;
    else if(temp == '-' || temp == 'z')
      calibration_factor -= 10;
    else if(temp == 's')
      calibration_factor += 100;  
    else if(temp == 'x')
      calibration_factor -= 100;  
    else if(temp == 'd')
      calibration_factor += 1000;  
    else if(temp == 'c')
      calibration_factor -= 1000;
    else if(temp == 'f')
      calibration_factor += 10000;  
    else if(temp == 'v')
      calibration_factor -= 10000;  
    else if(temp == 't')
      scale.tare();  //Reset the scale to zero
  }
}
//=============================================================================================
