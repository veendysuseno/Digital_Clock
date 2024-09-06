#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Wire.h>
#include <DS1307.h> 
#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void setup(){
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("  Jam Digital   ");
  lcd.setCursor(0,1);
  lcd.print(" ARDUINO UNO R3");
  delay(2000);
  lcd.clear();  
  RTC.stop();
  RTC.set(DS1307_SEC,1);        //set the seconds
  RTC.set(DS1307_MIN,23);     //set the minutes
  RTC.set(DS1307_HR,12);       //set the hours
  RTC.set(DS1307_DOW,4);       //set the day of the week
  RTC.set(DS1307_DATE,5);       //set the date
  RTC.set(DS1307_MTH,3);        //set the month
  RTC.set(DS1307_YR,9);         //set the year
  RTC.start();
}

void loop(){
  lcd.clear();
  lcd.print(RTC.get(DS1307_HR,true)); //read the hour and also update all the values by pushing in true
  lcd.print(":");
  lcd.print(RTC.get(DS1307_MIN,false));//read minutes without update (false)
  lcd.print(":");
  lcd.print(RTC.get(DS1307_SEC,false));//read seconds

  lcd.setCursor(0,1);
  lcd.print(RTC.get(DS1307_DATE,false));//read date
  lcd.print("/");
  lcd.print(RTC.get(DS1307_MTH,false));//read month
  lcd.print("/");
  lcd.print(RTC.get(DS1307_YR,false)); //read year 
  delay(1000);

}

