
float error_correction  = 3.5; //add this to actual value
int Range_sensitivity = 200; //Decrease this value to increase range 

#include <Wire.h> 
#include "MLX90615.h"

MLX90615 mlx = MLX90615();


void setup()
{
Serial.begin(9600);
delay(100);
while (! Serial);
pinMode(2,OUTPUT);
mlx.begin();
}

int Noise;
int Signal;
int Noise_P_Signal;
boolean trigger = true;
float temperature;
float pvs_temperature;

void loop()
{

lcd.setCursor(0,0);
 lcd.print("Time:  ");
 lcd.print(rtc.getTimeStr());
 
 lcd.setCursor(0,1);
 lcd.print("Date: ");
 lcd.print(rtc.getDateStr());
 

 
digitalWrite(2,HIGH);    // Turn on IR LED
delayMicroseconds(500);  // Forward rise time of IR LED
Noise_P_Signal=analogRead(A7);        // Read value from A0 => noise+signal
digitalWrite(2,LOW);     // Turn off IR LED
delayMicroseconds(500);  // Fall time of IR LED
Noise=analogRead(A7);        // Read value from A0 => noise only

Signal = Noise - Noise_P_Signal;


if (Signal>Range_sensitivity && Noise >500) //dec. signal to increase rage
{ 
  
  if (trigger == true)
   Serial.println("start");
   
   digitalWrite(2,LOW); //Turn off IR sensor to avoid interferance. 

   for (int i=1; i<=3; i++)
   {
   temperature = (mlx.get_object_temp()) + error_correction;
   Serial.println(temperature,1);
   delay(150);
   }

   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Temp:  ");
   lcd.print(temperature,1);
   

  trigger = false; 
}

else
{
  delay(100);
  trigger = true;
  digitalWrite(13,LOW);
  Serial.println("position_error");
}

 
}
