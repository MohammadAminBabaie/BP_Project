#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "outlier.h"
#include "stats.h"
#include "csv.h"
#include "utils.h"

void remove_outliers_iqr_inplace(
    CSV *csv,
    const char *col_name,
    double k)
{
    int col = find_column_index(csv, col_name);
    if (col < 0)
        return;

    double q1 = calculate_quartile(csv, col_name, 0.25);
    double q3 = calculate_quartile(csv, col_name, 0.75);
    double iqr = q3 - q1;

    double lower = q1 - k * iqr;
    double upper = q3 + k * iqr;

    int write_idx = 0;

    for (int i = 0; i < csv->rows; i++)
    {
        double v = atof(csv->data[i][col]);

        if (v >= lower && v <= upper)
        {
            // keep row
            csv->data[write_idx++] = csv->data[i];
        }
        else
        {
            // remove row → free memory
            for (int j = 0; j < csv->cols; j++)
                free(csv->data[i][j]);
            free(csv->data[i]);
        }
    }

    csv->rows = write_idx;
    csv->data = realloc(csv->data, csv->rows * sizeof(char **));
}
