#!/bin/bash

rm -r variants
mkdir variants

valuesFile=./operators_values.csv

k=0
while IFS=$';' read -r -a values; do
	echo -n "creating variant $k. "
	echo "Reduced operators bits ${values[@]}"
	mkdir variants/$k
	cat segmentation_head.c > variants/$k/segmentation.c
	for (( i = 0; i < ${#values[@]}; i++ )); do
		echo "::fap::FloatPrecTy OP_$i(8,${values[$i]});" >> variants/$k/segmentation.c
	done
	cat segmentation_tail.c >> variants/$k/segmentation.c

	g++ -Wall -fPIC -std=c++11 src/kmeans.c variants/$k/segmentation.c -I../code/include/ -I../code/include/segmentation/ src/fap.o -fPIC -o variants/$k/kmeans
	
	variants/$k/kmeans ../images/original.rgb variants/$k/original.rgb
	(( k=$k+1 ))
done < $valuesFile

echo "creating gold"
mkdir variants/gold
./kmeans_gold.out ../images/original.rgb variants/gold/original.rgb

chmod -R 777 variants
