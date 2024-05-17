#!/bin/bash

read -p "Even numbers to display upto? " num

count=0

while [ $count -le $num ]; do
	if (( $count % 2 == 0 )); then
		echo -n " $count"
	fi
	(( count++ ))
done

echo
echo "End of script"
