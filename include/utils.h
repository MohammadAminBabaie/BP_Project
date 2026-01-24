#ifndef UTILS_H
#define UTILS_H

char *strip(char *s);
int is_numeric(const char *s);
int find_column_index(CSV *csv, const char *col_name);

#endif
