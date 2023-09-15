#include <LiquidCrystal.h>
#include "print_stats.h"

extern LiquidCrystal e_lcd;

void print_the_speed(double velocity)
{
  e_lcd.setCursor(0, 0);
  e_lcd.print("speed");
  e_lcd.setCursor(12, 0);
  e_lcd.print("km/h");

  e_lcd.setCursor(6, 0);
  e_lcd.print(velocity);
  
}

void print_speed_stats(double current_average_velocity, double average_trip_velocity)
{  
  e_lcd.setCursor(0, 0);
  e_lcd.print("avg");
  e_lcd.setCursor(12, 0);
  e_lcd.print("km/h");
  e_lcd.setCursor(6, 0);
  e_lcd.print(current_average_velocity);

  e_lcd.setCursor(0, 1);
  e_lcd.print("t-avg");
  e_lcd.setCursor(12, 1);
  e_lcd.print("km/h");
  e_lcd.setCursor(6, 1);
  e_lcd.print(average_trip_velocity);
}

//trip distance
void print_the_dist(double trip_distance)
{
  e_lcd.setCursor(0, 0);
  e_lcd.print("trip");
  e_lcd.setCursor(14, 0);
  e_lcd.print("km");

  e_lcd.setCursor(6, 0);
  e_lcd.print(trip_distance);
}

//total distance, total average distance
void print_dist_stats(double total_distance, double average_trip_distance)
{
  e_lcd.setCursor(0, 0);
  e_lcd.print("t-avg");
  e_lcd.setCursor(14, 0);
  e_lcd.print("km");

  e_lcd.setCursor(6, 0);
  e_lcd.print(total_distance);

  e_lcd.setCursor(0, 1);
  e_lcd.print("total");
  e_lcd.setCursor(14, 1);
  e_lcd.print("km");
    
  e_lcd.setCursor(6, 1);
  e_lcd.print(average_trip_distance);
}

void print_the_time(double time_elapsed)
{
  e_lcd.setCursor(0, 0);
  e_lcd.print("time");
  e_lcd.setCursor(13, 0);
  e_lcd.print("min");

  e_lcd.setCursor(6, 0);
  e_lcd.print(time_elapsed);
}

//total distance, total average distance
void print_time_stats(double total_time, double average_trip_time)
{
  e_lcd.setCursor(0, 0);
  e_lcd.print("t-avg");
  e_lcd.setCursor(13, 0);
  e_lcd.print("h");

  e_lcd.setCursor(6, 0);
  e_lcd.print(average_trip_time);

  e_lcd.setCursor(0, 1);
  e_lcd.print("total");
  e_lcd.setCursor(13, 1);
  e_lcd.print("min");
    
  e_lcd.setCursor(6, 1);
  e_lcd.print(total_time);
}