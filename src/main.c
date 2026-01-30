#include <stdio.h>
#include <math.h>
#include <string.h>
#include "config.h"
#include "csv.h"
#include "impute.h"
#include "utils.h"
#include "plot.h"
#include "stats.h"
#include "feature_engineering.h"
#include "scaling.h"

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

        printf("\n>>> 2.Feature Engineering...\n");

        if (find_column_index(csv, "total_rooms") >= 0 &&
            find_column_index(csv, "households") >= 0)
        {
            add_divide_columns(
                csv,
                "total_rooms",
                "households",
                "rooms_per_household");
        }

        if (find_column_index(csv, "population") >= 0 &&
            find_column_index(csv, "households") >= 0)
        {
            add_divide_columns(
                csv,
                "population",
                "households",
                "population_per_household");
        }

        if (find_column_index(csv, "total_bedrooms") >= 0 &&
            find_column_index(csv, "total_rooms") >= 0)
        {
            add_divide_columns(
                csv,
                "total_bedrooms",
                "total_rooms",
                "bedrooms_per_room");
        }

        // if (find_column_index(csv, "latitude") >= 0 &&
        //     find_column_index(csv, "longitude") >= 0)
        // {
        //     add_multiply_columns(
        //         csv,
        //         "latitude",
        //         "longitude",
        //         "geo_interaction");
        // }

        remove_column(csv, "total_bedrooms");
        remove_column(csv, "population");
        remove_column(csv, "households");
        remove_column(csv, "total_rooms");

        printf("\n>>> 3.Feature Screening (Variance & Range)...\n");

        for (int col = 0; col < csv->cols; col++)
        {
            if (!is_numeric_column(csv, csv->headers[col]) || strcmp(csv->headers[col], TARGET_COL) == 0)
                continue;

            double var = calculate_variance(csv, csv->headers[col]);
            double maxv = calculate_maximum(csv, csv->headers[col]);
            double minv = calculate_minimum(csv, csv->headers[col]);
            double range = fabs(maxv - minv);

            printf("Column: %-25s | Var = %.6f | Range = %.3f\n", csv->headers[col], var, range);

            if (var < VAR_EPS)
            {
                printf(" -> Removing column (near-zero variance)\n");
                remove_column(csv, csv->headers[col]);
                col--;
                continue;
            }

            if (range > RANGE_LOG_THRESHOLD && minv > 0)
            {
                printf(" -> Applying log transform\n");
                log_transform_column(csv, csv->headers[col]);
            }
        }

        printf("\n>>> 4.Detecting text columns and applying OHE...\n\n");

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

    printf("\n>>> Exporting plot data...\n");

    for (int col = 0; col < csv->cols; col++)
    {
        char buffer[1000];
        snprintf(buffer, sizeof(buffer), "%s_vs_%s", csv->headers[col], TARGET_COL);

        char text_file[1000];
        snprintf(text_file, sizeof(buffer), "%s.%s", buffer, "txt");

        char gp_file[1000];
        snprintf(gp_file, sizeof(buffer), "%s.%s", buffer, "gp");

        export_points(
            csv,
            csv->headers[col],
            TARGET_COL,
            text_file);

        generate_gnuplot_script(
            text_file,
            gp_file,
            buffer,
            csv->headers[col],
            TARGET_COL);

        // run_gnuplot(gp_file);
    }

    free_csv(csv);
    return 0;
}
