#!/bin/bash

#checks for valid num of args (1)
if [[ $# -ne 1 ]]; then
	echo "wrong number of arguments" >&2 
	exit
fi

#checks if the course exists 
if [[ ! -f $1.txt ]]; then
	echo "course not found" >&2
	exit
fi

#checks if the dir exists and if it does, delets it and create a new one
if [[ -d  $1_stat ]]; then
	rm -r $1_stat
fi

mkdir $1_stat

#prints the second column to a temp txt file without the word "grades"
awk '{print $2}' $1.txt | tail +2 > ./$1_stat/grades.txt

#finds out the num of studets
num_of_students=$(wc -l < ./$1_stat/grades.txt)

#compiles the c prog with the grades and nym of students as args
gcc -g -Wall calc_statistics.c -o prog.exe

./prog.exe ./$1_stat/grades.txt $num_of_students

#prints the result created by the c prog
cat course_statistics.txt

mv course_statistics.txt $1_stat
