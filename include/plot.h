#ifndef PLOT_H
#define PLOT_H

#include "csv.h"

int export_points(
    CSV *csv,
    const char *x_col,
    const char *y_col,
    const char *filename);

int generate_gnuplot_script(
    const char *data_file,
    const char *script_file,
    const char *title,
    const char *xlabel,
    const char *ylabel);

void run_gnuplot(const char *script_file);

#endif
