#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stats.h"
#include "utils.h"
#include "impute.h"

static int cmp_double(const void *a, const void *b)
{
    double x = *(double *)a;
    double y = *(double *)b;
    return (x > y) - (x < y);
}

int count_missing(CSV *csv, const char *col_name)
{
    int col = find_column_index(csv, col_name);

    int count = 0;

    for (int i = 0; i < csv->rows; i++)
        if (is_missing(csv->data[i][col]))
            count++;

    return count;
}

double calculate_mean(CSV *csv, const char *col_name)
{
    int col = find_column_index(csv, col_name);

    double sum = 0;
    int count = 0;

    for (int i = 0; i < csv->rows; i++)
    {
        if (!is_missing(csv->data[i][col]) &&
            is_numeric(csv->data[i][col]))
        {

            sum += atof(csv->data[i][col]);
            count++;
        }
    }
    return count ? sum / count : 0;
}

double calculate_median(CSV *csv, const char *col_name)
{
    int col = find_column_index(csv, col_name);

    double *vals = malloc(csv->rows * sizeof(double));
    int n = 0;

    for (int i = 0; i < csv->rows; i++)
    {
        if (!is_missing(csv->data[i][col]) &&
            is_numeric(csv->data[i][col]))
        {

            vals[n++] = atof(csv->data[i][col]);
        }
    }

    if (n == 0)
    {
        free(vals);
        return 0;
    }

    qsort(vals, n, sizeof(double), cmp_double);

    double median = (n % 2)
                        ? vals[n / 2]
                        : (vals[n / 2 - 1] + vals[n / 2]) / 2.0;

    free(vals);
    return median;
}

char *calculate_mode(CSV *csv, const char *col_name)
{
    int col = find_column_index(csv, col_name);

    int max_count = 0;
    char *mode = NULL;

    for (int i = 0; i < csv->rows; i++)
    {
        if (is_missing(csv->data[i][col]))
            continue;

        int count = 0;
        for (int j = 0; j < csv->rows; j++)
        {
            if (!is_missing(csv->data[j][col]) &&
                strcmp(csv->data[i][col], csv->data[j][col]) == 0)
                count++;
        }

        if (count > max_count)
        {
            max_count = count;
            mode = csv->data[i][col];
        }
    }
    return mode;
}

double calculate_variance(CSV *csv, const char *col_name)
{
    int col = find_column_index(csv, col_name);
    if (col < 0)
        return NAN;

    double mean = 0.0;
    int count = 0;

    for (int i = 0; i < csv->rows; i++)
    {
        double x = to_double(csv->data[i][col]);
        if (!isnan(x))
        {
            mean += x;
            count++;
        }
    }

    if (count == 0)
        return NAN;
    mean /= count;

    double var = 0.0;
    for (int i = 0; i < csv->rows; i++)
    {
        double x = to_double(csv->data[i][col]);
        if (!isnan(x))
            var += (x - mean) * (x - mean);
    }

    return var / count;
}

double calculate_maximum(CSV *csv, const char *col_name)
{
    int col = find_column_index(csv, col_name);
    if (col < 0)
        return NAN;

    double max = -INFINITY;

    for (int i = 0; i < csv->rows; i++)
    {
        double x = to_double(csv->data[i][col]);
        if (!isnan(x) && x > max)
            max = x;
    }

    return max;
}

double calculate_minimum(CSV *csv, const char *col_name)
{
    int col = find_column_index(csv, col_name);
    if (col < 0)
        return NAN;

    double min = INFINITY;

    for (int i = 0; i < csv->rows; i++)
    {
        double x = to_double(csv->data[i][col]);
        if (!isnan(x) && x < min)
            min = x;
    }

    return min;
}