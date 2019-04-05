#!/bin/bash
i=0
j=0
feh --geometry 0x0 & 2> /dev/null
for k in $(seq 0 8); do
	echo "converting image ./variants/$k"
	python ../scripts/png2rgb.py png ./variants/$k/original.rgb ./variants/$k/$k.png > /dev/null
	x=$(echo "350*$i" |bc)
	y=$(echo "350*$j" |bc)
	python size.py "feh --geometry 200x200 ./variants/$k/$k.png" $x $y 17 30   
	((i=$i+1))
	if (( $i > 4 ));then
		i=0
		((j=$j+1))
	fi
done
	
	echo "converting image ./variants/gold"
	python ../scripts/png2rgb.py png ./variants/gold/original.rgb ./variants/gold/gold.png > /dev/null
	x=$(echo "350*$i" |bc)
	y=$(echo "350*$j" |bc)
	python size.py "feh --geometry 200x200 ./variants/gold/gold.png" $x $y 17 30  
	((i=$i+1))
	if (( $i > 4 ));then
		#i=0
		((j=$j+1))
	fi
	echo "converting original image"
	#python ../scripts/png2rgb.py png ../images/original.rgb ./original.png > /dev/null
	x=$(echo "350*$i" |bc)
	y=$(echo "350*$j" |bc)
	python size.py "feh --geometry 200x200 ./original.png" $x $y 17 30  
#killall feh
	