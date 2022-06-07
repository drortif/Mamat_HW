#!/bin/bash


#get the packets and clean whitespaces
packets=$(cat<&0|sed "s/' '/""/g")

#clean the rules from comments'whitespaces and empty lines
cleaned_rules=$(cat $1|sed "s/#.*/""/g"|sed "s/' '/""/g"|sed "/^$/d")


for line in $cleaned_rules

do
readarray -d,-t array_of_rules <<<$line

for rule in ${array_of_rules@}

do

echo $("$packets"|./firewall.exe $rule)>matching_packets.txt
done
cat matching_packets.txt>>packets_passed.txt
done

cat packets_passed.txt | sort | uniq | sed "/^$/d">&1
