#ifndef FEATURE_ENGINEERING_H
#define FEATURE_ENGINEERING_H

#include "csv.h"

// Arithmetic feature generation
void add_sum_columns(CSV *csv, const char *c1, const char *c2, const char *new_name);
void add_diff_columns(CSV *csv, const char *c1, const char *c2, const char *new_name);
void add_multiply_columns(CSV *csv, const char *c1, const char *c2, const char *new_name);
void add_divide_columns(CSV *csv, const char *c1, const char *c2, const char *new_name);

// Transformations
void log_transform_column(CSV *csv, const char *col_name);

#endif