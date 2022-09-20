// C++ code
//

#include <LiquidCrystal.h>

int seconds = 0;
int minutes = 0;
int hours = 0; //-1 for RISING condition

/* Button States for Hours and Minutes Buttons */
int buttonMinutes = 0;
int buttonHours = 0;

/* Variables for Input Noise */
int i = 0;
int f = 0;

LiquidCrystal lcd_1(12, 11, 5, 4, 7, 6);

void setup()
{
  lcd_1.begin(16, 2); 
  
  pinMode(2, INPUT_PULLUP); //button 1 
  pinMode(3, INPUT_PULLUP); //button 2 
 
  attachInterrupt(digitalPinToInterrupt(2), sumMinutes, FALLING);
  attachInterrupt(digitalPinToInterrupt(3), sumHours, FALLING);
  
  lcd_1.print("Time:");
  lcd_1.setCursor(6, 0);
  lcd_1.print("00:00:00"); //Time: 00:00:00
}

void loop()
{ 
  /* SECONDS CONDITION */
  if (seconds > 9) {
    lcd_1.setCursor(12, 0);
    lcd_1.print(seconds);
  }
  if (seconds < 10) {
    lcd_1.setCursor(13, 0);
    lcd_1.print(seconds);
  }
  
  /* 60 SECONDS -> 1 MINUTE*/
  if(seconds >= 60) {
    lcd_1.setCursor(12, 0);
    lcd_1.print(0);
    
    seconds = 0;
    minutes += 1;
    //seconds = 0;
  }
  
  /* MINUTES CONDITION */
  if (minutes > 9) {
    lcd_1.setCursor(9, 0);
    lcd_1.print(minutes);
  }
  if (minutes < 10) {
    lcd_1.setCursor(10, 0);
    lcd_1.print(minutes);
  }
  
  /* 60 MINUTES -> 1 HOUR */
  if (minutes >= 60) {
    lcd_1.setCursor(9, 0);
    lcd_1.print(0);
    
    hours += 1;
    minutes = 0;
  }
  
  /* HOURS CONDITION */
  if (hours > 9) {
    lcd_1.setCursor(6, 0);
    lcd_1.print(hours);
  }
  if (hours < 10) {
    lcd_1.setCursor(7, 0);
    lcd_1.print(hours);
  }
  if (hours >= 24) {
    lcd_1.setCursor(6, 0);
    lcd_1.print(0);
    lcd_1.setCursor(9, 0);
    lcd_1.print(0);
    lcd_1.setCursor(12, 0);
    lcd_1.print(0);
    seconds = 0;
    minutes = 0;
    hours = 0;
  }

  /* SUM 1 TO SECONDS */
  delay(1000); 
  seconds += 1;
}
void sumMinutes() {
  //minutes += 1;
  
  /* Prevent Input Noise */
  i = millis();
  if (i - f > 200)
    minutes += 1;
  f = i;
}

void sumHours() {
  //hours += 1;
  
  /* Prevent Input Noise */
  i = millis();
  if (i - f > 200)
    hours += 1;
  f = i;
}
