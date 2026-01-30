#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "scaling.h"
#include "utils.h"
#include "stats.h"

void min_max_scale_column(CSV *csv, const char *col_name)
{
    int col = find_column_index(csv, col_name);
    if (col < 0)
        return;

    double minv = calculate_minimum(csv, col_name);
    double maxv = calculate_maximum(csv, col_name);
    double range = maxv - minv;

    if (range == 0)
        return;

    for (int i = 0; i < csv->rows; i++)
    {
        if (is_missing(csv->data[i][col]))
            continue;

        double x = atof(csv->data[i][col]);
        double scaled = (x - minv) / range;

        char buf[64];
        sprintf(buf, "%.6f", scaled);

        free(csv->data[i][col]);
        csv->data[i][col] = strdup(buf);
    }
}

void standardize_column(CSV *csv, const char *col_name)
{
    int col = find_column_index(csv, col_name);
    if (col < 0)
        return;

    double mean = calculate_mean(csv, col_name);
    double std = calculate_std_deviation(csv, col_name);
    if (std == 0)
        return;

    for (int i = 0; i < csv->rows; i++)
    {
        if (is_missing(csv->data[i][col]))
            continue;

        double x = atof(csv->data[i][col]);
        double z = (x - mean) / std;

        char buf[64];
        sprintf(buf, "%.6f", z);

        free(csv->data[i][col]);
        csv->data[i][col] = strdup(buf);
    }
}

void robust_scale_column(CSV *csv, const char *col_name)
{
    int col = find_column_index(csv, col_name);
    if (col < 0)
        return;

    double median = calculate_median(csv, col_name);
    double q1 = calculate_quartile(csv, col_name, 0.25);
    double q3 = calculate_quartile(csv, col_name, 0.75);
    double iqr = q3 - q1;

    if (iqr == 0)
        return;

    for (int i = 0; i < csv->rows; i++)
    {
        if (is_missing(csv->data[i][col]))
            continue;

        double x = atof(csv->data[i][col]);
        double r = (x - median) / iqr;

        char buf[64];
        sprintf(buf, "%.6f", r);

        free(csv->data[i][col]);
        csv->data[i][col] = strdup(buf);
    }
}
