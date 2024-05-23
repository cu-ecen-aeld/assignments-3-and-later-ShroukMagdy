#!/bin/bash

if [ $# -eq 2 ]
then
	if [ ! -d "$1" ]
	then 
		echo First argument not a directory
		exit 1
	fi
else
	echo Arguments are not right
	exit 1
fi

no_files=$(ls $1 | wc -l) 
no_search=$(grep -r $2 $1 | wc -l)
echo The number of files are $no_files and the number of matching lines are $no_search



