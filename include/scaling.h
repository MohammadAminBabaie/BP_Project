#ifndef SCALING_H
#define SCALING_H

#include "csv.h"

// Min-Max
void min_max_scale_column(CSV *csv, const char *col_name);

// Z-score
void standardize_column(CSV *csv, const char *col_name);

// Robust
void robust_scale_column(CSV *csv, const char *col_name);

#endif
