/*
 * Chemwen0
 * By Doreen Chemweno
 * March 5th - April 2nd 2018
 * Load Cell HX711 Module Interface with Arduino to measure weight in Kgs
 Arduino 
 pin 
 5 -> HX711 CLK
 6 -> DOUT
 5V -> VCC
 GND -> GND
 
 Almost any pin on the Arduino Uno will be compatible with DOUT/CLK.
 The HX711 board can be powered from 2.7V to 5V so the Arduino 5V power should be fine.
*/
 
#include "HX711.h"  //You must have this library in your arduino library folder
#include <LiquidCrystal_I2C.h>


#define DOUT  6
#define CLK  5

LiquidCrystal_I2C lcd(0x3F,18,2); //important for display to work. Set the LCD Address and the dimensions of your LCD in terms of Columns and Lines.   
HX711 scale(DOUT, CLK);

//Change this calibration factor as per your load cell once it is found you many need to vary it in thousands
float calibration_factor = 102420; // 102420 worked for my 30Kg max scale setup 

// global Variables
int count;
//float sum = 0.00000;
float data,sum,newData;

//===========================================================================================================
//                                              FUNCTIONS
//===========================================================================================================

void stabilisingTime();
void stabilizingTime(){
//  lcd.setCursor(1,2);
  lcd.print("Please Wait...");
  delay(1000);
  lcd.clear();
//  lcd.setCursor(1,2);
  lcd.print("Place Item");
  delay(1000);
  lcd.clear();
  
}
void readData();
void readData(){
  sum = 0.0;
  for (count = 0; count<100; count++){
//      Serial.print("Weight: ");
      data = scale.get_units();  //Up to 3 decimal points
//      Serial.println(data);
      sum = sum + data;
//      Serial.println(data); //Change this to kg and re-adjust the calibration factor if you follow lbs
      lcd.setCursor(5,1);
      lcd.print(data);     
  }
  lcd.clear();
//  Serial.print("Sum Is ");
//  Serial.println(sum);
//  Serial.print("count is ");
//  Serial.println(count);
  newData = sum / count;
//  Serial.print("Averaged Data =  ");
  Serial.print(" ");
  Serial.print(newData);
  Serial.print(" kg "); //Change this to kg and re-adjust the calibration factor if you follow lbs
  Serial.print("|"); //separator for the App functioning. separates data entries.

  lcd.setCursor(1,0);
  lcd.print("Measured value is ");
  lcd.setCursor(4,1);
  lcd.print(newData);
  lcd.setCursor(9,1);
  lcd.print(" kg ");
  delay(10000);
  lcd.clear();
  
  delay(10);

  }
//=============================================================================================
//                         SETUP
//=============================================================================================
void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();  
  Serial.println("Press T to tare");
  stabilizingTime();
  scale.set_scale(102420);  //Calibration Factor obtained from first sketch
  scale.tare();             //Reset the scale to 0  
}
 
//=============================================================================================
//                         LOOP
//=============================================================================================
void loop() {

  readData();

//  if(Serial.available())
//  {
//    char temp = Serial.read();
//    if(temp == 't' || temp == 'T')
//      scale.tare();  //Reset the scale to zero      
//  }
}
//=============================================================================================
