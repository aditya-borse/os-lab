#!/bin/bash

read -p "Fibonacci squence of how many numbers: " num

a=0
b=1

echo -n "$a $b"

for (( i=1; i<=$(( num - 2 )); i++ )); do
	c=$(( a + b ))
	echo -n " $c"
	a=$b
	b=$c
done

echo
echo "End of script"
