#include <LiquidCrystal.h>
#include "printing.h"

extern LiquidCrystal lcd;

//print bars
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

//delete speed arrows
void dsarr(){
  lcd.setCursor(0, 0);
  lcd.write(' ');
  
  lcd.setCursor(6, 0);
  lcd.write(' ');
}

//print distance arrows
void pdarr(){
  lcd.setCursor(9, 0);
  lcd.write(byte(3));

  lcd.setCursor(15, 0);
  lcd.write(byte(2));
}

//delete distance arrows
void ddarr(){
  lcd.setCursor(9, 0);
  lcd.write(' ');

  lcd.setCursor(15, 0);
  lcd.write(' ');
}

//print power arrows
void pparr(){
  lcd.setCursor(0, 1);
  lcd.write(byte(3));

  lcd.setCursor(6, 1);
  lcd.write(byte(2));
}

//delete power arrows
void dparr(){
  lcd.setCursor(0, 1);
  lcd.write(' ');

  lcd.setCursor(6, 1);
  lcd.write(' ');
}

//print time arrows
void ptarr(){
  lcd.setCursor(9, 1);
  lcd.write(byte(3));

  lcd.setCursor(15, 1);
  lcd.write(byte(2));
}

//delete time arrows
void dtarr(){
  lcd.setCursor(9, 1);
  lcd.write(' ');

  lcd.setCursor(15, 1);
  lcd.write(' ');
}

//print "speed"
void pspeed(){
  lcd.setCursor(1, 0);
  lcd.print("speed");    
}

//print "dist"
void pdist(){
  lcd.setCursor(10, 0);
  lcd.print("dist");
  lcd.write(byte(4));
}

//print "power"
void ppower(){
  lcd.setCursor(1, 1);
  lcd.print("power"); 
}

//print "time"
void ptime(){
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
