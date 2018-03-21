
set terminal png

do for [i=1:32] {
	f(x) = 1./256
	a = i+1
	outfile = sprintf("graphes/graphe%d.png",i)
	set out outfile
	titre = sprintf("Position %d",i)
	set title titre
	set xlabel 'octet'
	set ylabel 'probabilité'
	set xrange [0:255]
	set yrange [0.003878:0.00395]
	plot "graphes/probabilitees.txt" u 1:a w l title "stats","courbeConstante.txt" u 1:2 w l title "1/256"
}


