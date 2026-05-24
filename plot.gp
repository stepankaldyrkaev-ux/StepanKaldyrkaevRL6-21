set terminal wxt
set multiplot
set title 'Circuit Work'
set palette defined (0 'green', 1 'blue', 2 'red', 3 'orange')
plot 'test.dat' using 1:2:(0) with lines,'test.dat' using 1:3:(1) with lines, 'test.dat' using 1:5:(3) with lines
unset multiplot
pause -1 'Press enter to close window'
