set title "longitude_vs_median_house_value"
set xlabel "longitude"
set ylabel "median_house_value"
set grid
plot "plots/longitude_vs_median_house_value.txt" using 1:2 with points pointtype 7 linecolor "blue" title "Data"
