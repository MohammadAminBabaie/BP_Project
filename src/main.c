#include <stdio.h>
#include "config.h"
#include "csv.h"

int main()
{
    printf(">>> Loading processed CSV file...\n");

    CSV *csv = load_csv(CSV_OUTPUT_FILE);

    if (!csv)
    {
        printf(">>> Failed to load processed CSV file.\n\n");

        printf(">>> Loading input CSV file...\n");
        csv = load_csv(CSV_INPUT_FILE);

        if (!csv)
        {
            printf(">>> Failed to load input CSV file.\n");
            return 1;
        }

        printf(">>> Input CSV loaded successfully!\n\n");

        printf(">>> Before processing:\n");

        printf("Rows: %d, Columns: %d\n\n", csv->rows, csv->cols);

        // Print headers
        printf("Headers:\n");
        for (int i = 0; i < csv->cols; i++)
        {
            printf("  [%d] %s\n", i, csv->headers[i]);
        }

        // Print the first few rows of data
        printf("\nData preview:\n");
        for (int i = 0; i < csv->rows && i < 3; i++)
        {
            for (int j = 0; j < csv->cols; j++)
            {
                printf("%s ", csv->data[i][j]);
            }
            printf("\n");
        }

        printf("\n>>> Processing...\n");

        printf("\n>>> 1.Detecting text columns and applying OHE...\n\n");

        // int col = 0;
        // while (col < csv->cols)
        // {
        //     if (!is_numeric_column(csv, csv->headers[col]))
        //     {

        //         printf("OHE applied on column: %s\n", csv->headers[col]);

        //         ohe_encode_column(csv, csv->headers[col]);
        //     }
        //     else
        //     {
        //         col++;
        //     }
        // }

        printf("OHE applied on column: %s\n", "ocean_proximity");

        printf("Before OHE: rows=%d cols=%d\n", csv->rows, csv->cols);

        ohe_encode_column(csv, "ocean_proximity");

        printf("After OHE: rows=%d cols=%d\n", csv->rows, csv->cols);

        printf("\n>>> Saving...\n");

        // Test saving CSV
        if (save_csv(CSV_OUTPUT_FILE, csv) == 0)
        {
            printf("\n>>> CSV saved successfully to processed.csv\n");
        }
        else
        {
            printf("\n>>> Failed to save CSV file.\n");
        }

        printf("\n>>> After processing:\n");
    }
    else
    {
        printf(">>> Processed CSV loaded successfully!\n");
    }

    printf("Rows: %d, Columns: %d\n\n", csv->rows, csv->cols);

    // Print headers
    printf("Headers:\n");
    for (int i = 0; i < csv->cols; i++)
    {
        printf("  [%d] %s\n", i, csv->headers[i]);
    }

    // Print the first few rows of data
    printf("\nData preview:\n");
    for (int i = 0; i < csv->rows && i < 3; i++)
    {
        for (int j = 0; j < csv->cols; j++)
        {
            printf("%s ", csv->data[i][j]);
        }
        printf("\n");
    }

    free_csv(csv);
    return 0;
}
