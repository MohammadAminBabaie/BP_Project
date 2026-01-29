set title "bedrooms_per_room_vs_median_house_value"
set xlabel "bedrooms_per_room"
set ylabel "median_house_value"
set grid
plot "plots/bedrooms_per_room_vs_median_house_value.txt" using 1:2 with points pointtype 7 linecolor "blue" title "Data"
