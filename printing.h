#ifndef PRINTING_H
#define PRINTING_H

#include <Arduino.h>

void print_bars();
void print_speed_arrows();
void delete_speed_arrows();
void print_distance_arrows();
void delete_distance_arrows();
void print_power_arrows();
void delete_power_arrows();
void print_time_arrows();
void delete_time_arrows();

void print_word_speed();
void print_word_dist();
void print_word_power();
void print_word_time();
void clear_screen();

#endif
