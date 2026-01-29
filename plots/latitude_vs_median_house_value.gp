set title "latitude_vs_median_house_value"
set xlabel "latitude"
set ylabel "median_house_value"
set grid
plot "plots/latitude_vs_median_house_value.txt" using 1:2 with points pointtype 7 linecolor "blue" title "Data"
