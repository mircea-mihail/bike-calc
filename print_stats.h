#ifndef PRINT_STATS_H
#define PRINT_STATS_H

#include <Arduino.h>

void print_the_speed(double velocity);
void print_speed_stats(double current_average_velocity, double average_trip_velocity);

void print_the_dist(double trip_distance);
void print_dist_stats(double total_distance, double average_trip_distance);

void print_the_time(double time_elapsed);
void print_time_stats(double total_time, double average_trip_time);

#endif
