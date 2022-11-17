#include <LiquidCrystal.h>
#include "print_stats.h"

extern LiquidCrystal lcd;

//instatnt speed
void print_the_speed(double v){
  lcd.setCursor(0, 0);
  lcd.print("speed");
  lcd.setCursor(12, 0);
  lcd.print("km/h");

  lcd.setCursor(6, 0);
  lcd.print(v);
  
}

//average velocity, total average velocity
void print_speed_averages(double av, double tav){
  
  lcd.setCursor(0, 0);
  lcd.print("avg");
  lcd.setCursor(12, 0);
  lcd.print("km/h");
  lcd.setCursor(6, 0);
  lcd.print(av);

  lcd.setCursor(0, 1);
  lcd.print("t-avg");
  lcd.setCursor(12, 1);
  lcd.print("km/h");
  lcd.setCursor(6, 1);
  lcd.print(tav);
}

//trip distance
void print_the_dist(double d){
  lcd.setCursor(0, 0);
  lcd.print("trip");
  lcd.setCursor(14, 0);
  lcd.print("km");

  lcd.setCursor(6, 0);
  lcd.print(d);
}

//total distance, total average distance
void print_dist_stats(double td, double tad){
  lcd.setCursor(0, 0);
  lcd.print("t-avg");
  lcd.setCursor(14, 0);
  lcd.print("km");

  lcd.setCursor(6, 0);
  lcd.print(td);

  lcd.setCursor(0, 1);
  lcd.print("total");
  lcd.setCursor(14, 1);
  lcd.print("km");
    
  lcd.setCursor(6, 1);
  lcd.print(tad);
}