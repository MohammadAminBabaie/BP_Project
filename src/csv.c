#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv.h"
#include "utils.h"

char *read_line(FILE *file)
{
    char *line = NULL;
    size_t size = 0;
    int ch; // ASCII code

    while ((ch = fgetc(file)) != EOF && ch != '\n')
    {
        char *temp = realloc(line, size + 2);
        if (!temp)
        {
            free(line);
            return NULL;
        }
        line = temp;
        line[size++] = ch;
    }

    if (size == 0 && ch == EOF)
        return NULL;

    line[size] = '\0';
    return line;
}

int count_columns(const char *line)
{
    int count = 1;
    for (int i = 0; line[i]; i++)
    {
        if (line[i] == ',')
            count++;
    }
    return count;
}

char *strndup_safe(const char *src, size_t n)
{
    if (!src)
        return strdup("");

    size_t len = strlen(src);
    if (len > n)
        len = n;

    char *out = malloc(len + 1);
    if (!out)
        return NULL;

    memcpy(out, src, len);
    out[len] = '\0';
    return out;
}

char **parse_csv_row(const char *line, int cols)
{
    char **row = malloc(cols * sizeof(char *));
    int col = 0;

    const char *start = line;
    const char *p = line;

    while (*p && col < cols)
    {
        if (*p == ',')
        {
            row[col++] = strndup_safe(start, p - start);
            start = p + 1;
        }
        p++;
    }

    if (col < cols)
        row[col++] = strndup_safe(start, p - start);

    while (col < cols)
        row[col++] = strdup("");

    return row;
}

CSV *load_csv(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
        return NULL;

    CSV *csv = malloc(sizeof(CSV));
    csv->rows = 0;

    // Read header
    char *line = read_line(file);
    if (!line)
        return NULL;

    csv->cols = count_columns(line);
    csv->headers = malloc(csv->cols * sizeof(char *));

    char *token = strtok(line, ",");
    for (int i = 0; i < csv->cols; i++)
    {
        csv->headers[i] = strdup(token);
        token = strtok(NULL, ",");
    }
    free(line);

    // Read data
    csv->data = NULL;

    while ((line = read_line(file)))
    {
        csv->data = realloc(csv->data, (csv->rows + 1) * sizeof(char **));
        csv->data[csv->rows] = parse_csv_row(line, csv->cols);

        csv->rows++;
        free(line);
    }

    fclose(file);
    return csv;
}

int save_csv(const char *filename, CSV *csv)
{
    FILE *file = fopen(filename, "w");
    if (!file)
        return -1;

    // Write header
    for (int i = 0; i < csv->cols; i++)
    {
        fprintf(file, "%s", csv->headers[i]);
        if (i < csv->cols - 1)
            fprintf(file, ",");
    }
    fprintf(file, "\n");

    // Write data
    for (int i = 0; i < csv->rows; i++)
    {
        for (int j = 0; j < csv->cols; j++)
        {
            fprintf(file, "%s", csv->data[i][j]);
            if (j < csv->cols - 1)
                fprintf(file, ",");
        }
        fprintf(file, "\n");
    }

    fclose(file);
    return 0;
}

void free_csv(CSV *csv)
{
    for (int i = 0; i < csv->cols; i++)
        free(csv->headers[i]);
    free(csv->headers);

    for (int i = 0; i < csv->rows; i++)
    {
        for (int j = 0; j < csv->cols; j++)
            free(csv->data[i][j]);
        free(csv->data[i]);
    }

    free(csv->data);
    free(csv);
}

void add_column(CSV *csv, const char *col_name)
{
    csv->headers = realloc(csv->headers, (csv->cols + 1) * sizeof(char *));
    csv->headers[csv->cols] = strdup(col_name);

    for (int i = 0; i < csv->rows; i++)
    {
        csv->data[i] = realloc(csv->data[i], (csv->cols + 1) * sizeof(char *));
        csv->data[i][csv->cols] = strdup("");
    }

    csv->cols++;

    printf(" Add %s column.\n", col_name);
}

void remove_column(CSV *csv, const char *col_name)
{
    int col = find_column_index(csv, col_name);
    if (col < 0)
        return;

    free(csv->headers[col]);
    for (int i = col; i < csv->cols - 1; i++)
        csv->headers[i] = csv->headers[i + 1];

    for (int i = 0; i < csv->rows; i++)
    {
        free(csv->data[i][col]);
        for (int j = col; j < csv->cols - 1; j++)
            csv->data[i][j] = csv->data[i][j + 1];
    }

    csv->cols--;

    printf(" Remove %s column.\n", col_name);
}

void copy_headers_except(CSV *dest, CSV *src, const char *target)
{
    int tcol = find_column_index(src, target);
    int d = 0;

    for (int i = 0; i < src->cols; i++)
    {
        if (i == tcol)
            continue;
        dest->headers[d++] = strdup(src->headers[i]);
    }
}

CSV *create_empty_csv(int feat_count)
{
    CSV *csv = malloc(sizeof(CSV));
    if (!csv)
        return NULL;

    csv->rows = 0;
    csv->cols = feat_count;

    csv->headers = malloc(feat_count * sizeof(char *));
    for (int i = 0; i < feat_count; i++)
        csv->headers[i] = NULL;

    csv->data = NULL;
    return csv;
}

void append_row(CSV *csv, char **row, int col_count)
{
    if (!csv || !row || col_count != csv->cols)
        return;

    csv->data = realloc(csv->data, (csv->rows + 1) * sizeof(char **));
    if (!csv->data)
        return;

    csv->data[csv->rows] = malloc(col_count * sizeof(char *));
    if (!csv->data[csv->rows])
        return;

    for (int j = 0; j < col_count; j++)
    {
        if (row[j])
            csv->data[csv->rows][j] = strdup(row[j]);
        else
            csv->data[csv->rows][j] = strdup("");
    }

    csv->rows++;
}