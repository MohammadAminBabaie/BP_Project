#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "impute.h"
#include "stats.h"
#include "utils.h"

int is_missing(const char *s)
{
    if (!s || *s == '\0')
        return 1;

    const char *missing[] = {
        "NA", "NaN", "N/A", "?", "-", "null", " "};

    for (int i = 0; i < 6; i++)
        if (strcmp(s, missing[i]) == 0)
            return 1;

    if (strcmp(s, "-999") == 0)
        return 1;

    return 0;
}

void mean_imputation(CSV *csv, const char *col_name)
{
    int col = find_column_index(csv, col_name);
    if (col < 0)
        return;

    double mean = calculate_mean(csv, col_name);

    char buf[64];
    sprintf(buf, "%.3f", mean);

    printf("Mean of column %s: %s\n", col_name, buf);

    for (int i = 0; i < csv->rows; i++)
    {
        if (is_missing(csv->data[i][col]))
        {
            free(csv->data[i][col]);
            csv->data[i][col] = strdup(buf);
        }
    }
}

void median_imputation(CSV *csv, const char *col_name)
{
    int col = find_column_index(csv, col_name);
    if (col < 0)
        return;

    double median = calculate_median(csv, col_name);

    char buf[64];
    sprintf(buf, "%.3f", median);

    printf("Median of column %s: %s\n", col_name, buf);

    for (int i = 0; i < csv->rows; i++)
    {
        if (is_missing(csv->data[i][col]))
        {
            free(csv->data[i][col]);
            csv->data[i][col] = strdup(buf);
        }
    }
}

void mode_imputation(CSV *csv, const char *col_name)
{
    int col = find_column_index(csv, col_name);
    if (col < 0)
        return;

    char *mode = calculate_mode(csv, col_name);
    if (!mode)
        return;

    printf("Mode of column %s: %s\n", col_name, mode);

    for (int i = 0; i < csv->rows; i++)
    {
        if (is_missing(csv->data[i][col]))
        {
            free(csv->data[i][col]);
            csv->data[i][col] = strdup(mode);
        }
    }

    free(mode);
}

void forward_fill(CSV *csv, const char *col_name)
{
    int col = find_column_index(csv, col_name);
    if (col < 0)
        return;

    char *last = NULL;

    for (int i = 0; i < csv->rows; i++)
    {
        if (!is_missing(csv->data[i][col]))
        {
            last = csv->data[i][col];
        }
        else if (last)
        {
            free(csv->data[i][col]);
            csv->data[i][col] = strdup(last);
        }
    }
}

void backward_fill(CSV *csv, const char *col_name)
{
    int col = find_column_index(csv, col_name);
    if (col < 0)
        return;

    char *next = NULL;

    for (int i = csv->rows - 1; i >= 0; i--)
    {
        if (!is_missing(csv->data[i][col]))
        {
            next = csv->data[i][col];
        }
        else if (next)
        {
            free(csv->data[i][col]);
            csv->data[i][col] = strdup(next);
        }
    }
}
