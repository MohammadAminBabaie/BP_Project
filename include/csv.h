#ifndef CSV_H
#define CSV_H

typedef struct
{
    char **headers; // headers[col]
    char ***data;   // data[row][col]
    int rows;
    int cols;
} CSV;

CSV *load_csv(const char *filename);
int save_csv(const char *filename, CSV *csv);
void free_csv(CSV *csv);

int is_numeric_column(CSV *csv, const char *col_name);
void ohe_encode_column(CSV *csv, const char *col_name);

#endif
