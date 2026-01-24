#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "csv.h"

char *strip(char *s)
{
    if (!s)
        return NULL;

    // Trim left
    while (isspace((unsigned char)*s))
        s++;

    if (*s == '\0')
        return s;

    // Trim right
    char *end = s + strlen(s) - 1;
    while (end > s && isspace((unsigned char)*end))
        end--;

    *(end + 1) = '\0';
    return s;
}

int is_numeric(const char *s)
{
    if (!s || *s == '\0')
        return 0;
    char *end;
    strtod(s, &end);
    return *end == '\0';
}

int find_column_index(CSV *csv, const char *col_name)
{
    for (int i = 0; i < csv->cols; i++)
    {
        if (strcmp(csv->headers[i], col_name) == 0)
            return i;
    }
    return -1;
}
