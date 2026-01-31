#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "split.h"
#include "stats.h"
#include "utils.h"

int *get_feature_indices(CSV *csv, int target_col, int *out_count)
{
    int *idx = malloc(csv->cols * sizeof(int));
    int c = 0;

    for (int i = 0; i < csv->cols; i++)
        if (i != target_col)
            idx[c++] = i;

    *out_count = c;
    return idx;
}

void extract_xy(
    CSV *csv,
    int *rows, int n_rows,
    int target_col,
    CSV *X,
    double *y)
{
    int feat_count;
    int *feat_idx = get_feature_indices(csv, target_col, &feat_count);

    for (int i = 0; i < n_rows; i++)
    {
        int r = rows[i];

        // y
        y[i] = atof(csv->data[r][target_col]);

        // X row
        char **row = malloc(feat_count * sizeof(char *));
        for (int j = 0; j < feat_count; j++)
            row[j] = strdup(csv->data[r][feat_idx[j]]);

        append_row(X, row, feat_count);
    }

    free(feat_idx);
}

MLDataSplit train_test_split(
    CSV *csv,
    const char *target_col,
    double test_ratio)
{
    srand(time(NULL));

    int target = find_column_index(csv, target_col);
    int n = csv->rows;
    int test_size = (int)(n * test_ratio);
    int train_size = n - test_size;

    int *used = calloc(n, sizeof(int));
    int *test_idx = malloc(test_size * sizeof(int));
    int *train_idx = malloc(train_size * sizeof(int));

    for (int i = 0; i < test_size; i++)
    {
        int r;
        do
        {
            r = rand() % n;
        } while (used[r]);
        used[r] = 1;
        test_idx[i] = r;
    }

    int t = 0;
    for (int i = 0; i < n; i++)
        if (!used[i])
            train_idx[t++] = i;

    int feat_count;
    get_feature_indices(csv, target, &feat_count);

    CSV *x_train = create_empty_csv(feat_count);
    CSV *x_test = create_empty_csv(feat_count);

    copy_headers_except(x_train, csv, target_col);
    copy_headers_except(x_test, csv, target_col);

    double *y_train = malloc(train_size * sizeof(double));
    double *y_test = malloc(test_size * sizeof(double));

    extract_xy(csv, train_idx, train_size, target, x_train, y_train);
    extract_xy(csv, test_idx, test_size, target, x_test, y_test);

    free(used);

    return (MLDataSplit){
        x_train, x_test,
        y_train, y_test,
        train_size, test_size};
}

MLDataSplit stratified_split(
    CSV *csv,
    const char *target_col,
    double test_ratio)
{
    int target = find_column_index(csv, target_col);
    int n = csv->rows;
    int bins = 10;

    double minv = calculate_minimum(csv, target_col);
    double maxv = calculate_maximum(csv, target_col);
    double step = (maxv - minv) / bins;

    int **bucket = malloc(bins * sizeof(int *));
    int *count = calloc(bins, sizeof(int));
    for (int i = 0; i < bins; i++)
        bucket[i] = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        double v = atof(csv->data[i][target]);
        int b = (int)((v - minv) / step);
        if (b == bins)
            b--;
        bucket[b][count[b]++] = i;
    }

    int *train_idx = malloc(n * sizeof(int));
    int *test_idx = malloc(n * sizeof(int));
    int tr = 0, te = 0;

    for (int b = 0; b < bins; b++)
    {
        int test_n = (int)(count[b] * test_ratio);
        for (int i = 0; i < count[b]; i++)
        {
            if (i < test_n)
                test_idx[te++] = bucket[b][i];
            else
                train_idx[tr++] = bucket[b][i];
        }
    }

    int feat_count;
    get_feature_indices(csv, target, &feat_count);

    CSV *x_train = create_empty_csv(feat_count);
    CSV *x_test = create_empty_csv(feat_count);

    copy_headers_except(x_train, csv, target_col);
    copy_headers_except(x_test, csv, target_col);

    double *y_train = malloc(tr * sizeof(double));
    double *y_test = malloc(te * sizeof(double));

    extract_xy(csv, train_idx, tr, target, x_train, y_train);
    extract_xy(csv, test_idx, te, target, x_test, y_test);

    return (MLDataSplit){
        x_train, x_test,
        y_train, y_test,
        tr, te};
}
