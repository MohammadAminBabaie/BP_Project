#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv.h"
#include "utils.h"

void ohe_encode_column(CSV *csv, const char *col_name)
{
    int col = find_column_index(csv, col_name);
    if (col < 0)
        return;

    // Collect unique values
    char **unique = NULL;
    int unique_count = 0;

    for (int i = 0; i < csv->rows; i++)
    {
        char *val = csv->data[i][col];
        if (!val || *val == '\0')
            continue;

        int found = 0;
        for (int j = 0; j < unique_count; j++)
        {
            if (strcmp(unique[j], val) == 0)
            {
                found = 1;
                break;
            }
        }

        if (!found && !is_numeric(val))
        {
            char **tmp = realloc(unique, (unique_count + 1) * sizeof(char *));
            if (!tmp)
                goto cleanup;

            unique = tmp;
            unique[unique_count++] = strdup(val);
        }
    }

    if (unique_count == 0)
        goto cleanup;

    // Resize headers
    int old_cols = csv->cols;
    int new_cols = old_cols + unique_count - 1;

    char **new_headers = realloc(csv->headers, new_cols * sizeof(char *));
    if (!new_headers)
        goto cleanup;

    csv->headers = new_headers;

    // Shift headers right
    for (int i = old_cols - 1; i > col; i--)
        csv->headers[i + unique_count - 1] = csv->headers[i];

    // Insert new headers
    for (int i = 0; i < unique_count; i++)
    {
        char buffer[128];
        snprintf(buffer, sizeof(buffer), "%s_%s", col_name, unique[i]);
        csv->headers[col + i] = strdup(buffer);
    }

    // Process rows
    for (int i = 0; i < csv->rows; i++)
    {
        char *cell = csv->data[i][col]
                         ? strdup(csv->data[i][col])
                         : strdup("");

        char **new_row = realloc(csv->data[i], new_cols * sizeof(char *));
        if (!new_row)
        {
            free(cell);
            goto cleanup;
        }

        csv->data[i] = new_row;

        // Shift row cells
        for (int k = old_cols - 1; k > col; k--)
            csv->data[i][k + unique_count - 1] = csv->data[i][k];

        // Insert OHE values
        for (int j = 0; j < unique_count; j++)
        {
            csv->data[i][col + j] =
                strcmp(cell, unique[j]) == 0
                    ? strdup("1")
                    : strdup("0");
        }

        free(cell);
    }

    // Remove old header
    free(csv->headers[col + unique_count]); // original column header

    csv->cols = new_cols;

cleanup:
    for (int i = 0; i < unique_count; i++)
        free(unique[i]);
    free(unique);
}
