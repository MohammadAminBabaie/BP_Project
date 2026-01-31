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

// Column management
void add_column(CSV *csv, const char *col_name);
void remove_column(CSV *csv, const char *col_name);

CSV *create_empty_csv(int feat_count);
void copy_headers_except(CSV *dest, CSV *src, const char *target);
void append_row(CSV *csv, char **row, int col_count);

#endif
