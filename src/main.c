#include <stdio.h>
#include "config.h"
#include "csv.h"
#include "impute.h"
#include "utils.h"
#include "plot.h"

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

        printf(">>> 1.Detecting incomplete rows...\n");

        int incomplete_count = 0;

        for (int i = 0; i < csv->rows; i++)
        {
            if (is_row_incomplete(csv, i))
            {
                printf("Row %d is incomplete\n", i);
                incomplete_count++;
            }
        }

        printf("Total incomplete rows: %d\n\n", incomplete_count);

        printf(">>> Filling missing values...\n");

        // for (int i = 0; i < csv->cols; i++)
        // {
        //     mode_imputation(csv, csv->headers[i]);
        // }

        // Numeric columns
        median_imputation(csv, "longitude");
        median_imputation(csv, "latitude");
        median_imputation(csv, "housing_median_age");
        median_imputation(csv, "total_bedrooms");
        median_imputation(csv, "total_rooms");
        median_imputation(csv, "population");
        median_imputation(csv, "households");
        median_imputation(csv, "median_income");
        median_imputation(csv, "median_house_value");

        // Categorical columns
        mode_imputation(csv, "ocean_proximity");

        printf("\n>>> Re-checking incomplete rows after imputation...\n");

        incomplete_count = 0;

        for (int i = 0; i < csv->rows; i++)
        {
            if (is_row_incomplete(csv, i))
            {
                printf("Row %d is STILL incomplete\n", i);
                incomplete_count++;
            }
        }

        if (incomplete_count == 0)
            printf("All missing values successfully filled. \n");
        else
            printf("Remaining incomplete rows: %d \n", incomplete_count);

        printf("\n>>> 2.Detecting text columns and applying OHE...\n\n");

        printf("Before OHE: rows=%d cols=%d\n", csv->rows, csv->cols);

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

    printf("\n>>> Exporting plot data...\n");

    export_points(
        csv,
        "median_income",
        "median_house_value",
        "points.txt");

    generate_gnuplot_script(
        "points.txt",
        "plot.gp",
        "House Prices vs Income",
        "Median Income",
        "Median House Value");

    run_gnuplot("plot.gp");

    free_csv(csv);
    return 0;
}
