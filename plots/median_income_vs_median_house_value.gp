set title "median_income_vs_median_house_value"
set xlabel "median_income"
set ylabel "median_house_value"
set grid
plot "plots/median_income_vs_median_house_value.txt" using 1:2 with points pointtype 7 linecolor "blue" title "Data"
