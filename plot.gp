reset
set xlabel 'total copy length (bits)'
set ylabel 'time (ns)'
set title 'bitcpy runtime'
set term png enhanced font 'Verdana,10'
set output 'result.png'
set grid
plot [1:][0:20000] \
'out_plot' using 1:2 with linespoints linewidth 2 title "bitcpy",\
'' using 1:3 with linespoints linewidth 2 title "bitcpy renew"