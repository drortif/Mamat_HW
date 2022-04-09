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

#prints the second column to a temp txt file
awk '{print $2}' $1.txt > temp_grades.txt

#takes all the rows accept the first one (cuz of the word "grades")
sed 1,1d temp_grades.txt > grades.txt

rm temp_grades.txt

mv grades.txt $1_stat

#cwd is the one we created
cd $1_stat

#finds out the num of studets
num_of_students=$(wc -l < grades.txt)

#put it in a file cuz we didnt find out how to send a int veriable
num_of_students > num_of_students.txt

#compiles the c prog with the grades and nym of students as args
gcc -g -Wall calc_statistics.c -o prog.exe

./prog.exe grades.txt num_of_students.txt

#prints the result created by the c prog
cat course_statistics.txt
