#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "plot.h"
#include "utils.h"
#include "config.h"
#include "impute.h"

int export_points(
    CSV *csv,
    const char *x_col,
    const char *y_col,
    const char *filename)
{
    int x = find_column_index(csv, x_col);
    int y = find_column_index(csv, y_col);

    if (x < 0 || y < 0)
        return -1;

    char file_path[500];

    snprintf(file_path, sizeof(file_path), "%s%s", PROJECT_PLOTS_PATH, filename);

    FILE *f = fopen(file_path, "w");
    if (!f)
        return -1;

    for (int i = 0; i < csv->rows; i++)
    {
        char *xs = csv->data[i][x];
        char *ys = csv->data[i][y];

        if (is_missing(xs) || is_missing(ys))
            continue;

        if (!is_numeric(xs) || !is_numeric(ys))
            continue;

        fprintf(f, "%f %f\n", atof(xs), atof(ys));
    }

    fclose(f);
    return 0;
}

int generate_gnuplot_script(
    const char *data_file,
    const char *script_file,
    const char *title,
    const char *xlabel,
    const char *ylabel)
{
    char data_file_path[500];
    char script_file_path[500];

    snprintf(data_file_path, sizeof(data_file_path), "%s%s", PROJECT_PLOTS_PATH, data_file);
    snprintf(script_file_path, sizeof(script_file_path), "%s%s", PROJECT_PLOTS_PATH, script_file);

    FILE *f = fopen(script_file_path, "w");
    if (!f)
        return -1;

    fprintf(f, "set title \"%s\"\n", title);
    fprintf(f, "set xlabel \"%s\"\n", xlabel);
    fprintf(f, "set ylabel \"%s\"\n", ylabel);
    fprintf(f, "set grid\n");

    fprintf(
        f,
        "plot \"%s\" using 1:2 with points pointtype 7 linecolor \"blue\" title \"Data\"\n",
        data_file_path);

    fclose(f);
    return 0;
}

void run_gnuplot(const char *script_file)
{
    char script_file_path[500];

    snprintf(script_file_path, sizeof(script_file_path), "%s%s", PROJECT_PLOTS_PATH, script_file);

    char cmd[256];
    snprintf(cmd, sizeof(cmd), "gnuplot -persist %s", script_file_path);
    system(cmd);
}
