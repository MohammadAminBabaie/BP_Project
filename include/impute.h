#ifndef IMPUTE_H
#define IMPUTE_H

#include "csv.h"

int is_missing(const char *s);

void mean_imputation(CSV *csv, const char *col_name);
void median_imputation(CSV *csv, const char *col_name);
void mode_imputation(CSV *csv, const char *col_name);

void forward_fill(CSV *csv, const char *col_name);
void backward_fill(CSV *csv, const char *col_name);

#endif
