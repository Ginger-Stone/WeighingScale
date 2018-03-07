#include <HX711_ADC.h>
#include <LCD03.h>
#include <Wire.h>

HX711_ADC scale(A1, A0);
LCD03 lcd;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("Dee Limited for Cedarlab Technics.");
scale.begin();
long stabilisingtime = 3000; // tare preciscion can be improved by adding a few seconds of stabilising time
scale.start(stabilisingtime);
scale.setCalFactor(94450.0); 

lcd.begin(20,3);
Wire.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  scale.update();
  float data=scale.getData();
  Serial.println(data);
  Wire.println(data);
  delay(5000);
//  float sum=0.00;
//  int count=0;
//  
//  if (count<11){
//    float data=scale.getData();
//    Serial.print("set: ");
//    Serial.println(data);
//    sum=sum+data;
//  count++;
//  }
//  float avg=sum/count;
//    lcd.write(avg);
//  Serial.println(avg);
//  delay(5000);

}
