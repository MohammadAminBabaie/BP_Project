set title "log_population_per_household_vs_median_house_value"
set xlabel "log_population_per_household"
set ylabel "median_house_value"
set grid
plot "plots/log_population_per_household_vs_median_house_value.txt" using 1:2 with points pointtype 7 linecolor "blue" title "Data"
