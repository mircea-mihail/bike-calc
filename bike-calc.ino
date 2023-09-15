#include <LiquidCrystal.h>
#include "printing.h"
#include "print_stats.h"

#define PICK_BUTTON 2
#define SELECTOR_TRESHOLD 10
#define SELECTOR_POT A0

static const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
extern LiquidCrystal e_lcd(rs, en, d4, d5, d6, d7);

const int g_nMaxAnalogVal = 1023;

int current_selection, previous_selection;
//distance
double g_fTripDistance;
double g_fTotalDistance;
double g_fAverageTripDistance;

//velocity
double g_fVelocity;
double g_fCurrentAverageVelocity;
double g_fAverageTripVelocity;

//time
double g_fTimeElapsed;
double g_fTotalTime;
double g_fAverageTripTime;

//power
double g_fPower;
double g_fTotalPower;
double g_fAverageTripPower;

void setup()
{
  Serial.begin(9600);
  pinMode(PICK_BUTTON, INPUT_PULLUP);

  //builds custom characters to be displayed
  const byte inner_pipe_right[8]  = { 0b00001, 0b00001, 0b00001, 0b00001, 0b00001, 0b00001, 0b00001, 0b00001 };
  const byte inner_pipe_left[8]   = { 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000 };
  const byte left_arrow[8]        = { 0b00010, 0b00110, 0b01111, 0b11111, 0b11111, 0b01111, 0b00110, 0b00010 };
  const byte right_arrow[8]       = { 0b01000, 0b01100, 0b11110, 0b11111, 0b11111, 0b11110, 0b01100, 0b01000 };
  const byte kms[8]               = { 0b10010, 0b10100, 0b11000, 0b10110, 0b00000, 0b00000, 0b11010, 0b10101 };
  const byte clock[8]             = { 0b00000, 0b01110, 0b11011, 0b11011, 0b11001, 0b11111, 0b01110, 0b00000 };
  
  e_lcd.createChar(0, inner_pipe_left);
  e_lcd.createChar(1, inner_pipe_right);
  e_lcd.createChar(2, left_arrow);
  e_lcd.createChar(3, right_arrow);
  e_lcd.createChar(4, kms);
  e_lcd.createChar(5, clock);

  e_lcd.begin(16, 2);

  //initialisations:
  g_fTripDistance = 0;
  g_fTotalDistance = 0;
  g_fAverageTripDistance = 0;
}

//timer
//math
//stop time, do math
//start timer
#define WHEEL_PERIMETER 76.2 //wheel size
#define DESIRED_MAGNET_DETECTIONS 4

void do_the_math();
void speed_menu();
void dist_menu();
void time_menu();
void power_menu();
void print_the_menu();

void loop() 
{
  current_selection = analogRead(SELECTOR_POT);
  print_the_menu();
  previous_selection = current_selection;
}


//ROUGH at the moment

//returns true if any actual math has been done
void do_the_math()
{
  int nMagnetDetections = 0;
  unsigned long unStartTimer, unLapTimer;
  bool bMagnetSensorTrigger = false;

  while(true)
  {
    //magnet sensor
    int nSensorRead = analogRead(A5);
  
    if(nMagnetDetections == 0){
      unStartTimer = micros();
    }
  
    if(nSensorRead <= 520){
      bMagnetSensorTrigger = false;
    }
  
    if(nSensorRead > 520 && !bMagnetSensorTrigger){
      nMagnetDetections ++;
      g_fTripDistance += WHEEL_PERIMETER;
      bMagnetSensorTrigger = true;
    }
  
    //after a number of full wheel rotations counted by nMagnetDetections, the speed is calculated
    if(nMagnetDetections == DESIRED_MAGNET_DETECTIONS){
      unLapTimer = micros();
      
      g_fVelocity = (DESIRED_MAGNET_DETECTIONS * WHEEL_PERIMETER)/(unLapTimer - unStartTimer);
      
      nMagnetDetections = 0;
    }
  }
}

void print_sub_menu(void (*print_main_value)(double), void (*print_stats)(double, double), 
              double main_value, double first_stat, double second_stat )
{
   clear_screen();

  int times_pressed = 0;
  int current_btn_read = digitalRead(PICK_BUTTON);
  int previous_btn_read = current_btn_read;
  
  while(   previous_selection < current_selection + SELECTOR_TRESHOLD 
        && previous_selection > current_selection - SELECTOR_TRESHOLD
       )
  {
    current_btn_read = digitalRead(PICK_BUTTON);

    if(previous_btn_read != current_btn_read){
      times_pressed += 1;   
      previous_btn_read = current_btn_read;
      if(times_pressed % 2 == 0)
        clear_screen();
    }

    if(times_pressed % 4 >= 2){
      (*print_stats)(first_stat, second_stat);
    } 
    else
      (*print_main_value)(main_value);

    if(times_pressed == 8) 
      times_pressed = 0;

    current_selection = analogRead(SELECTOR_POT);
  }
}

void time_menu()
{
  clear_screen();
  while(previous_selection < current_selection + SELECTOR_TRESHOLD && previous_selection > current_selection - SELECTOR_TRESHOLD)
  {
    e_lcd.setCursor(0, 0);
    e_lcd.print(" it's time bro ");
    current_selection = analogRead(SELECTOR_POT);
  }
}

void power_menu()
{
  clear_screen();
  while(previous_selection < current_selection + SELECTOR_TRESHOLD && previous_selection > current_selection - SELECTOR_TRESHOLD)
  {
    e_lcd.setCursor(0, 0);
    e_lcd.print("UNLIMITED POWER!");
    current_selection = analogRead(SELECTOR_POT);
  }
}

void print_the_menu()
{
  print_bars();
  print_word_speed();
  print_word_dist();
  print_word_power();
  print_word_time();

  //speed
  if(current_selection >= g_nMaxAnalogVal / 4 * 3){
    print_speed_arrows();
    if(digitalRead(PICK_BUTTON) == 0){
      // speed_menu();
      print_sub_menu((void (*)(double))(&print_the_speed), (void (*)(double, double))(&print_speed_stats),
                      g_fVelocity, g_fCurrentAverageVelocity, g_fAverageTripVelocity);
    }
  }
  else
    delete_speed_arrows();
  
  //distance
  if(current_selection < g_nMaxAnalogVal / 4 * 3 && current_selection >= g_nMaxAnalogVal / 2){    
    print_distance_arrows();
    if(digitalRead(PICK_BUTTON) == 0){
      print_sub_menu((void (*)(double))(&print_the_dist), (void (*)(double, double))(&print_dist_stats),
                      g_fTripDistance, g_fTotalDistance, g_fAverageTripDistance);
    }
  }
  else
    delete_distance_arrows();
  
  //time
  if(current_selection < g_nMaxAnalogVal / 2 && current_selection >= g_nMaxAnalogVal / 4){
    print_time_arrows();
    if(digitalRead(PICK_BUTTON) == 0){
      time_menu();
    }
  }
  else
    delete_time_arrows();

  //power
  if(current_selection < g_nMaxAnalogVal / 4){
    print_power_arrows();
    if(digitalRead(PICK_BUTTON) == 0){
      power_menu();
    }
  }
  else
    delete_power_arrows();  
}
