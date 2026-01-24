#include "csv.h"
#include "utils.h"

int is_numeric_column(CSV *csv, const char *col_name)
{
    int col = find_column_index(csv, col_name);
    if (col < 0)
        return 0;

    for (int i = 0; i < csv->rows; i++)
    {
        if (!is_numeric(strip(csv->data[i][col])))
            return 0;
    }
    return 1;
}
