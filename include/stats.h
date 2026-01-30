#ifndef STATS_H
#define STATS_H

#include "csv.h"

double calculate_mean(CSV *csv, const char *col_name);
double calculate_median(CSV *csv, const char *col_name);
char *calculate_mode(CSV *csv, const char *col_name);

int count_missing(CSV *csv, const char *col_name);

double calculate_variance(CSV *csv, const char *col_name);
double calculate_maximum(CSV *csv, const char *col_name);
double calculate_minimum(CSV *csv, const char *col_name);
double calculate_std_deviation(CSV *csv, const char *col_name);
double calculate_quartile(CSV *csv, const char *col_name, double q);

#endif
