set title "housing_median_age_vs_median_house_value"
set xlabel "housing_median_age"
set ylabel "median_house_value"
set grid
plot "plots/housing_median_age_vs_median_house_value.txt" using 1:2 with points pointtype 7 linecolor "blue" title "Data"
