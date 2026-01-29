set title "ocean_proximity_4.177778_vs_median_house_value"
set xlabel "ocean_proximity_4.177778"
set ylabel "median_house_value"
set grid
plot "plots/ocean_proximity_4.177778_vs_median_house_value.txt" using 1:2 with points pointtype 7 linecolor "blue" title "Data"
