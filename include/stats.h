#ifndef STATS_H
#define STATS_H

#include "csv.h"

double calculate_mean(CSV *csv, const char *col_name);
double calculate_median(CSV *csv, const char *col_name);
char *calculate_mode(CSV *csv, const char *col_name);

int count_missing(CSV *csv, const char *col_name);

#endif
