#include <LcdEffects.h>
#include <Effects.h>
#include <LiquidCrystal.h>
#define pick 2

const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int selector, max_analog_val = 1023;
int lastsel;

double d, td;           //distance, total distance
double v, tv;        //velocity
double te, tte;      //time elapsed
double power, tpower;

byte inner_pipe_r[8] = {
  0b00001,
  0b00001,
  0b00001,
  0b00001,
  0b00001,
  0b00001,
  0b00001,
  0b00001
};

byte inner_pipe_l[8] = {
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000
};

byte larrow[8] = {
  0b00010,
  0b00110,
  0b01111,
  0b11111,
  0b11111,
  0b01111,
  0b00110,
  0b00010
};

byte rarrow[8] = {
  0b01000,
  0b01100,
  0b11110,
  0b11111,
  0b11111,
  0b11110,
  0b01100,
  0b01000
};

byte kms[8] = {
  0b10010,
  0b10100,
  0b11000,
  0b10110,
  0b00000,
  0b00000,
  0b11010,
  0b10101
};

byte time[8] = {
  0b00000,
  0b01110,
  0b11011,
  0b11011,
  0b11001,
  0b11111,
  0b01110,
  0b00000
};

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
  
void pbars(){
  lcd.setCursor(7, 0);
  lcd.write(byte(1));
  lcd.write(byte(0));
  
  lcd.setCursor(7, 1);
  lcd.write(byte(1));
  lcd.write(byte(0));
}

//print speed arrows
void psarr(){
  lcd.setCursor(0, 0);
  lcd.write(byte(3));

  lcd.setCursor(6, 0);
  lcd.write(byte(2));
}

void dsarr(){
  lcd.setCursor(0, 0);
  lcd.write(' ');

  lcd.setCursor(6, 0);
  lcd.write(' ');
}

void pdarr(){
  lcd.setCursor(9, 0);
  lcd.write(byte(3));

  lcd.setCursor(15, 0);
  lcd.write(byte(2));
}

void ddarr(){
  lcd.setCursor(9, 0);
  lcd.write(' ');

  lcd.setCursor(15, 0);
  lcd.write(' ');
}

void pparr(){
  lcd.setCursor(0, 1);
  lcd.write(byte(3));

  lcd.setCursor(6, 1);
  lcd.write(byte(2));
}

void dparr(){
  lcd.setCursor(0, 1);
  lcd.write(' ');

  lcd.setCursor(6, 1);
  lcd.write(' ');
}

void ptarr(){
  lcd.setCursor(9, 1);
  lcd.write(byte(3));

  lcd.setCursor(15, 1);
  lcd.write(byte(2));
}

void dtarr(){
  lcd.setCursor(9, 1);
  lcd.write(' ');

  lcd.setCursor(15, 1);
  lcd.write(' ');
}

void pspeed(){
  lcd.setCursor(1, 0);
  lcd.print("speed");    
}

void pdist(){
  lcd.setCursor(10, 0);
  lcd.print("dist");
  lcd.write(byte(4));
}

void ppower(){
  lcd.setCursor(1, 1);
  lcd.print("power"); 
}

void pptime(){
  lcd.setCursor(10, 1);
  lcd.print("time"); 
  lcd.write(byte(5));
}

void clear_screen(){
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
}

void print_the_speed(){
  v = 46.3;

  lcd.setCursor(0, 0);
  lcd.print("speed");
  lcd.setCursor(12, 0);
  lcd.print("km/h");

  lcd.setCursor(6, 0);
  lcd.print(v);
  
}

void print_speed_stats(){
  tv = 123/5;

  lcd.setCursor(0, 1);
  lcd.print("t-avg");
  lcd.setCursor(12, 1);
  lcd.print("km/h");
  lcd.setCursor(6, 1);
  lcd.print(tv-2.1);

  lcd.setCursor(0, 0);
  lcd.print("avg");
  lcd.setCursor(12, 0);
  lcd.print("km/h");

  lcd.setCursor(6, 0);
  lcd.print(tv);
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
      print_speed_stats();
    } 
    else
      print_the_speed();

    if(tp == 8) 
      tp = 0;
  }
}

void print_the_dist(){
  lcd.setCursor(0, 0);
  lcd.print("trip");
  lcd.setCursor(14, 0);
  lcd.print("km");

  lcd.setCursor(6, 0);
  lcd.print(d);
}

void print_dist_stats(){
  lcd.setCursor(0, 0);
  lcd.print("t-avg");
  lcd.setCursor(14, 0);
  lcd.print("km");

  lcd.setCursor(6, 0);
  lcd.print(d-7.21);

  lcd.setCursor(0, 1);
  lcd.print("total");
  lcd.setCursor(14, 1);
  lcd.print("km");
    
  lcd.setCursor(6, 1);
  lcd.print(td);
}

void dist_menu(){
  clear_screen();
  //times pressed
  int tp = 0;//0
  //previous press
  int cur_read = digitalRead(pick);
  int pp = cur_read;
  
  d = 12.3;
  td = d * 53;

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
      print_dist_stats();
    } 
    else
      print_the_dist();

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
  pptime();

  Serial.print(selector); Serial.print('\n');
  Serial.print(max_analog_val/4); Serial.print('\n');
  
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
