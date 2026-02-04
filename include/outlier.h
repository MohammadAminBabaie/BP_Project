#ifndef OUTLIER_H
#define OUTLIER_H

#include "csv.h"

void remove_outliers_iqr_inplace(
    CSV *csv,
    const char *col_name,
    double k);

#endif
