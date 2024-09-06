# Arduino Digital Clock with DS1307 RTC and LCD Display

## Description

This project demonstrates how to create a digital clock using an Arduino Uno, a DS1307 real-time clock (RTC) module, and a 16x2 LCD display. The clock displays the current time (hours, minutes, and seconds) and date (day, month, and year) on the LCD screen.

## Components

- Arduino Uno R3
- DS1307 RTC module
- 16x2 LCD Display
- Jumper wires
- Breadboard

## Libraries Required

- **Wire.h**: For I2C communication with the DS1307 RTC module.
- **DS1307.h**: For interacting with the DS1307 RTC module.
- **LiquidCrystal.h**: For controlling the 16x2 LCD display.

## Wiring Diagram

| Component         | Arduino Pin |
| ----------------- | ----------- |
| SDA (DS1307)      | A4          |
| SCL (DS1307)      | A5          |
| LCD RS            | 2           |
| LCD Enable        | 3           |
| LCD D4            | 4           |
| LCD D5            | 5           |
| LCD D6            | 6           |
| LCD D7            | 7           |
| 5V (LCD, DS1307)  | 5V          |
| GND (LCD, DS1307) | GND         |

## Code

```cpp
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Wire.h>
#include <DS1307.h>
#include <LiquidCrystal.h>

// Initialize the LCD with the interface pins
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void setup() {
  Serial.begin(9600);      // Start the serial communication
  lcd.begin(16, 2);        // Initialize the 16x2 LCD
  lcd.print("  Jam Digital   ");
  lcd.setCursor(0, 1);
  lcd.print(" ARDUINO UNO R3");
  delay(2000);
  lcd.clear();

  // Initialize the DS1307 RTC
  RTC.stop();              // Stop the RTC before setting the time
  RTC.set(DS1307_SEC, 1);  // Set seconds
  RTC.set(DS1307_MIN, 23); // Set minutes
  RTC.set(DS1307_HR, 12);  // Set hours
  RTC.set(DS1307_DOW, 4);  // Set day of the week
  RTC.set(DS1307_DATE, 5); // Set date
  RTC.set(DS1307_MTH, 3);  // Set month
  RTC.set(DS1307_YR, 9);   // Set year
  RTC.start();             // Start the RTC
}

void loop() {
  lcd.clear();

  // Display time (hours:minutes:seconds)
  lcd.print(RTC.get(DS1307_HR, true));  // Get hours and update all values
  lcd.print(":");
  lcd.print(RTC.get(DS1307_MIN, false)); // Get minutes
  lcd.print(":");
  lcd.print(RTC.get(DS1307_SEC, false)); // Get seconds

  // Move to the second line to display date (day/month/year)
  lcd.setCursor(0, 1);
  lcd.print(RTC.get(DS1307_DATE, false)); // Get date
  lcd.print("/");
  lcd.print(RTC.get(DS1307_MTH, false));  // Get month
  lcd.print("/");
  lcd.print(RTC.get(DS1307_YR, false));   // Get year

  delay(1000);  // Wait for 1 second before updating again
}
```

## How It Works

1. RTC Setup: The DS1307 RTC module keeps track of the current time and date, even when the Arduino is powered off. The RTC.set() function is used in the setup() to initialize the time to 12:23:01 on 5th March 2009.

2. LCD Display: The time and date are displayed on a 16x2 LCD screen. The time (hours, minutes, and seconds) is shown on the first line, while the date (day, month, and year) is displayed on the second line.

3. Main Loop: In the loop(), the time and date are refreshed every second using the RTC.get() function to read from the RTC module and display it on the LCD.

## Usage

1. Connect the components according to the wiring diagram.
2. Upload the code to your Arduino Uno.
3. The time and date will be displayed on the LCD screen, and the clock will update every second.

## Notes

- To set the time, modify the values in the RTC.set() functions inside setup().
- The DS1307 RTC module has an onboard battery that keeps the time even when the Arduino is powered off.
