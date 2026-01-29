#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "feature_engineering.h"
#include "csv.h"
#include "utils.h"

void add_sum_columns(CSV *csv, const char *c1, const char *c2, const char *new_name)
{
    int a = find_column_index(csv, c1);
    int b = find_column_index(csv, c2);
    if (a < 0 || b < 0)
        return;

    add_column(csv, new_name);
    int out = csv->cols - 1;

    for (int i = 0; i < csv->rows; i++)
    {
        double x = to_double(csv->data[i][a]);
        double y = to_double(csv->data[i][b]);
        if (isnan(x) || isnan(y))
            continue;

        char buf[64];
        sprintf(buf, "%.6f", x + y);
        free(csv->data[i][out]);
        csv->data[i][out] = strdup(buf);
    }
}

void add_diff_columns(CSV *csv, const char *c1, const char *c2, const char *new_name)
{
    int a = find_column_index(csv, c1);
    int b = find_column_index(csv, c2);
    if (a < 0 || b < 0)
        return;

    add_column(csv, new_name);
    int out = csv->cols - 1;

    for (int i = 0; i < csv->rows; i++)
    {
        double x = to_double(csv->data[i][a]);
        double y = to_double(csv->data[i][b]);
        if (isnan(x) || isnan(y))
            continue;

        char buf[64];
        sprintf(buf, "%.6f", x - y);
        free(csv->data[i][out]);
        csv->data[i][out] = strdup(buf);
    }
}

void add_multiply_columns(CSV *csv, const char *c1, const char *c2, const char *new_name)
{
    int a = find_column_index(csv, c1);
    int b = find_column_index(csv, c2);
    if (a < 0 || b < 0)
        return;

    add_column(csv, new_name);
    int out = csv->cols - 1;

    for (int i = 0; i < csv->rows; i++)
    {
        double x = to_double(csv->data[i][a]);
        double y = to_double(csv->data[i][b]);
        if (isnan(x) || isnan(y))
            continue;

        char buf[64];
        sprintf(buf, "%.6f", x * y);
        free(csv->data[i][out]);
        csv->data[i][out] = strdup(buf);
    }
}

void add_divide_columns(CSV *csv, const char *c1, const char *c2, const char *new_name)
{
    int a = find_column_index(csv, c1);
    int b = find_column_index(csv, c2);
    if (a < 0 || b < 0)
        return;

    add_column(csv, new_name);
    int out = csv->cols - 1;

    for (int i = 0; i < csv->rows; i++)
    {
        double x = to_double(csv->data[i][a]);
        double y = to_double(csv->data[i][b]);
        if (isnan(x) || isnan(y) || y == 0)
            continue;

        char buf[64];
        sprintf(buf, "%.6f", x / y);
        free(csv->data[i][out]);
        csv->data[i][out] = strdup(buf);
    }
}

void log_transform_column(CSV *csv, const char *col_name)
{
    int col = find_column_index(csv, col_name);
    if (col < 0)
        return;

    for (int i = 0; i < csv->rows; i++)
    {
        double x = to_double(csv->data[i][col]);
        if (isnan(x) || x <= 0)
            continue;

        char buf[64];
        sprintf(buf, "%.6f", log(x));
        free(csv->data[i][col]);
        csv->data[i][col] = strdup(buf);
    }

    // Change header

    char buffer[500];
    snprintf(buffer, sizeof(buffer), "%s_%s", "log", col_name);

    free(csv->headers[col]);
    csv->headers[col] = strdup(buffer);
}