#!/bin/zsh
# Issue the following commands before running this script:
#   xset s off
#   xset -dpms
#   xautolock -disable
# AND DO NOT FORGET TO SET GRAPHICS CARD TO "PERFORMANCE" MODE!!


# should be at least 3, as the highest & lowest values are discarded
RUNS=5

# no need to update anything below this line
############################################

AWKPROG='
	BEGIN {
		highestfps = 0;
		lowestfps = 0;
		highestmem = 0;
		lowestmem = 0;
		fpssum = 0;
		memsum = 0;
		count = 0;
	}
	{
		if (highestfps == 0 || $1 > highestfps) {
			highestfps = $1;
		}
		if (lowestfps == 0 || $1 < lowestfps) {
			lowestfps = $1;
		}
		if (highestmem == 0 || $2 > highestmem) {
			highestmem = $2;
		}
		if (lowestmem == 0 || $2 < lowestmem) {
			lowestmem = $2;
		}
		fpssum = fpssum + $1;
		memsum = memsum + $2;
		count = count + 1;
	}
	END {
		printf "%f %f\n", (fpssum - (highestfps + lowestfps)) / (count - 2), (memsum - (highestmem + lowestmem)) / (count - 2);
	}
'

make -j8 || exit

for APP in 6 7 81 82 9 10 11; do

	PURGE_LINE=$(for i in `seq $RUNS`; do
		./PURGEDemo $APP purge 2>/dev/null
	done | awk "$AWKPROG")

	OGRE_LINE=$(for i in `seq $RUNS`; do
		./PURGEDemo $APP ogre 2>/dev/null
	done | awk "$AWKPROG")

	echo $PURGE_LINE $OGRE_LINE | awk '{printf "\\begin{table}[htpb]\n\t\\center\n\t\\caption{Performance metrics for TestScene'$APP'}\n\t\\begin{tabular}{l | l | l | l}\n\t\t& without PURGE & with PURGE & relative value\\\\ \\hline\n\t\tFrames per second & %.2f & %.2f & %.2f\\%%\\\\\n\t\tPeak memory usage & %d & %d & %.2f\\%%\\\\\n\t\\end{tabular}\n\t\\label{tbl:Performance'$APP'}\n\\end{table}\n", $3, $1, (100 * $1 / $3), $4, $2, (100 * $2 / $4)}'
	echo

done

