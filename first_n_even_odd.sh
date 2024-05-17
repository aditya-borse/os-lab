#!/bin/bash

read -p "How many even odd numbers? " n

echo -n "Even numbers:"

for(( i=0; i < $(( $n * 2 )); i+=2 )); do
	echo -n " $i"
done

echo 
echo -n "Odd numbers:"

for (( i=1; i < $(( $n * 2 )); i+=2)); do
	echo -n " $i"
done

echo 
echo "End of script"
