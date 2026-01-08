#include <stdio.h>
#include "config.h"
#include "csv.h"

int main()
{
    CSV *csv = load_csv(CSV_INPUT_FILE);

    if (!csv)
    {
        printf("Failed to load CSV file.\n");
        return 1;
    }

    printf("CSV loaded successfully!\n");
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

    // Test saving CSV
    if (save_csv(CSV_OUTPUT_FILE, csv) == 0)
    {
        printf("\nCSV saved successfully to output.csv\n");
    }
    else
    {
        printf("\nFailed to save CSV file.\n");
    }

    free_csv(csv);
    return 0;
}
