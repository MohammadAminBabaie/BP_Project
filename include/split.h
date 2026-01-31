#ifndef SPLIT_H
#define SPLIT_H

#include "csv.h"

typedef struct
{
    CSV *x_train;
    CSV *x_test;
    double *y_train;
    double *y_test;
    int train_size;
    int test_size;
} MLDataSplit;

MLDataSplit train_test_split(CSV *csv, const char *target_col, double test_ratio);
MLDataSplit stratified_split(CSV *csv, const char *target_col, double test_ratio);

#endif