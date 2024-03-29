#include <LiquidCrystal.h>
#include "printing.h"

#define INNER_PIPE_LEFT 0 
#define INNER_PIPE_RIGHT 1
#define LEFT_ARROW 2
#define RIGHT_ARROW 3
#define KMS 4
#define CLOCK 5

extern LiquidCrystal e_lcd;

void print_bars(){
  e_lcd.setCursor(7, 0);
  e_lcd.write(byte(INNER_PIPE_RIGHT));
  e_lcd.write(byte(INNER_PIPE_LEFT));
  
  e_lcd.setCursor(7, 1);
  e_lcd.write(byte(INNER_PIPE_RIGHT));
  e_lcd.write(byte(INNER_PIPE_LEFT));
}

void print_speed_arrows(){
  e_lcd.setCursor(0, 0);
  e_lcd.write(byte(RIGHT_ARROW));

  e_lcd.setCursor(6, 0);
  e_lcd.write(byte(LEFT_ARROW));
}

void delete_speed_arrows(){
  e_lcd.setCursor(0, 0);
  e_lcd.write(' ');
  
  e_lcd.setCursor(6, 0);
  e_lcd.write(' ');
}

void print_distance_arrows(){
  e_lcd.setCursor(9, 0);
  e_lcd.write(byte(RIGHT_ARROW));

  e_lcd.setCursor(15, 0);
  e_lcd.write(byte(LEFT_ARROW));
}

void delete_distance_arrows(){
  e_lcd.setCursor(9, 0);
  e_lcd.write(' ');

  e_lcd.setCursor(15, 0);
  e_lcd.write(' ');
}

void print_power_arrows(){
  e_lcd.setCursor(0, 1);
  e_lcd.write(byte(RIGHT_ARROW));

  e_lcd.setCursor(6, 1);
  e_lcd.write(byte(LEFT_ARROW));
}

void delete_power_arrows(){
  e_lcd.setCursor(0, 1);
  e_lcd.write(' ');

  e_lcd.setCursor(6, 1);
  e_lcd.write(' ');
}

void print_time_arrows(){
  e_lcd.setCursor(9, 1);
  e_lcd.write(byte(RIGHT_ARROW));

  e_lcd.setCursor(15, 1);
  e_lcd.write(byte(LEFT_ARROW));
}

void delete_time_arrows(){
  e_lcd.setCursor(9, 1);
  e_lcd.write(' ');

  e_lcd.setCursor(15, 1);
  e_lcd.write(' ');
}

void print_word_speed(){
  e_lcd.setCursor(1, 0);
  e_lcd.print("speed");    
}

void print_word_dist(){
  e_lcd.setCursor(10, 0);
  e_lcd.print("dist");
  e_lcd.write(byte(KMS));
}

void print_word_power(){
  e_lcd.setCursor(1, 1);
  e_lcd.print("power"); 
}

void print_word_time(){
  e_lcd.setCursor(10, 1);
  e_lcd.print("time"); 
  e_lcd.write(byte(CLOCK));
}

void clear_screen(){
  e_lcd.setCursor(0, 0);
  e_lcd.print("                ");
  e_lcd.setCursor(0, 1);
  e_lcd.print("                ");
}
