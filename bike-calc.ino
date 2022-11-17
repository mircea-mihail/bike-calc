#include <LiquidCrystal.h>
#include "printing.h"
#include "print_stats.h"
#define pick 2

const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int selector, lastsel; //math counter
const int max_analog_val = 1023;
//ws = wheel size
double d = 0, td = 0, tad = 0;     //distance, total distance, total average distance
double v = -1, av = -1, tav = -1;     //velocity
double te, tte;        //time elapsed
double power, tpower;

//aesthetic purposes
byte inner_pipe_r[8] = { 0b00001, 0b00001, 0b00001, 0b00001, 0b00001, 0b00001, 0b00001, 0b00001 };
byte inner_pipe_l[8] = { 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000 };
byte larrow[8]       = { 0b00010, 0b00110, 0b01111, 0b11111, 0b11111, 0b01111, 0b00110, 0b00010 };
byte rarrow[8]       = { 0b01000, 0b01100, 0b11110, 0b11111, 0b11111, 0b11110, 0b01100, 0b01000 };
byte kms[8]          = { 0b10010, 0b10100, 0b11000, 0b10110, 0b00000, 0b00000, 0b11010, 0b10101 };
byte time[8]         = { 0b00000, 0b01110, 0b11011, 0b11011, 0b11001, 0b11111, 0b01110, 0b00000 };

void setup() {
  Serial.begin(9600);
  pinMode(pick, INPUT_PULLUP);
  lcd.createChar(0, inner_pipe_l);
  lcd.createChar(1, inner_pipe_r);
  lcd.createChar(2, larrow);
  lcd.createChar(3, rarrow);
  lcd.createChar(4, kms);
  lcd.createChar(5, time);
  lcd.begin(16, 2);
}

//timer
//math
//stop time, do math
//start timer
const double ws = 76.2;
const int no_counts = 4;
int math_count = 0;
unsigned long start, lap;
bool flip = false;

//ROUGH at the moment

bool do_the_math(){
  //magnet sensor
  int mag_sens = analogRead(A5);

  if(math_count == 0){
    start = micros();
  }

  if(mag_sens <= 520){
    flip = true;
  }
  Serial.print(mag_sens);
  Serial.print('\n');
  delay(100);


  if(mag_sens > 520 && flip){
    Serial.print(mag_sens);
    Serial.print('\n');
    math_count ++;
    d += ws;
    flip = false;
  }

  if(math_count == no_counts){
    lap = micros();
    v = (no_counts * ws)/(lap - start);
    math_count = 0;
    return true;
  }

  return false;
}

void speed_menu(){
  clear_screen();
  //times pressed;
  int tp = 0;//0
  //previous press
  int cur_read = digitalRead(pick);
  int pp = cur_read;
  while(lastsel < selector + 20 && lastsel > selector - 20){
    
    selector = analogRead(A0);
    cur_read = digitalRead(pick);

    if(pp != cur_read){
      tp += 1;   
      pp = cur_read;
      if(tp % 2 == 0)
        clear_screen();
    }

    if(tp % 4 >= 2){
      print_speed_averages(av, tav);
    } 
    else
      print_the_speed(v);

    if(tp == 8) 
      tp = 0;
  }
}

void dist_menu(){
  clear_screen();
  //times pressed
  int tp = 0;//0
  //previous press
  int cur_read = digitalRead(pick);
  int pp = cur_read;

  while(lastsel < selector + 10 && lastsel > selector - 10){
    selector = analogRead(A0);
    
    cur_read = digitalRead(pick);

    if(pp != cur_read){
      tp += 1;   
      pp = cur_read;
      if(tp % 2 == 0)
        clear_screen();
    }

    if(tp % 4 >= 2){
      print_dist_stats(td, tad);
    } 
    else
      print_the_dist(d);

    if(tp == 8) 
      tp = 0; 
  }
}

void time_menu(){
  clear_screen();
  while(lastsel < selector + 10 && lastsel > selector - 10){
    selector = analogRead(A0);
    lcd.setCursor(0, 0);
    lcd.print(" it's time bro ");
  }
}

void power_menu(){
  clear_screen();
  while(lastsel < selector + 10 && lastsel > selector - 10){
    selector = analogRead(A0);
    lcd.setCursor(0, 0);
    lcd.print("UNLIMITED POWER!");
  }
}

void loop() {
  selector = analogRead(A0);
  pbars();
  pspeed();
  pdist();
  ppower();
  ptime();

  do_the_math();

  //speed
  if(selector >= max_analog_val / 4 * 3){
    psarr();
    if(digitalRead(pick) == 0){
      speed_menu();
    }
  }
  else
    dsarr();
  
  //distance
  if(selector < max_analog_val / 4 * 3 && selector >= max_analog_val / 2){    
    pdarr();
    if(digitalRead(pick) == 0){
      dist_menu();
    }
  }
  else
    ddarr();
  
  //time
  if(selector < max_analog_val / 2 && selector >= max_analog_val / 4){
    ptarr();
    if(digitalRead(pick) == 0){
      time_menu();
    }
  }
  else
    dtarr();

  //power
  if(selector < max_analog_val / 4){
    pparr();
    if(digitalRead(pick) == 0){
      power_menu();
    }
  }
  else
    dparr();  

  lastsel = selector;
    
}
