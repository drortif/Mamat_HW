#!/bin/bash



>packets_passed.txt
#get the packets and clean whitespaces
PACKETS=$(cat| tr -d "[:blank:]")

#clean the rules from comments'whitespaces and empty lines
RULES=$(grep -o "^[^#].*" $1 | sed 's/#.*/ /' |tr -d "[:blank:]"| sed '/^$/d')

while read -r RULE;
do
	PORTDST=$(echo $RULE | grep -o "dst-port[\.=0-9\-]\+")
	PORTSRC=$(echo $RULE | grep -o "src-port[\.=0-9\-]\+")
	IPDST=$(echo $RULE | grep -o "dst-ip[\.=0-9/]\+")
	IPSRC=$(echo $RULE | grep -o "src-ip[\.=0-9/]\+")
	
	echo "$PACKETS" | ./firewall.exe "$IPSRC" | ./firewall.exe "$IPDST" | ./firewall.exe 		"$PORTSRC" | ./firewall.exe "$PORTDST" >>packets.txt
	
done <<< "$RULES"

cat packets.txt | sort | uniq >&1

rm packets.txt
	
	 
#for line in $rules_cleaned

#do

#echo $packets > matching_packets.txt
#readarray -d,-t array_of_rules <<<"$line"

#for rule in ${array_of_rules[@]}

#do
#echo $(cat matching_packets.txt|./firewall.exe "$rule") >>matching packets.txt

#done
#cat matching_packets.txt>>packets_passed.txt
#done
#sed -i "s/\ /\n/g" packets_passed.txt

#cat packets_passed.txt| sort | uniq| sed "/^$/d" >ready_to_print.txt

#cat ready_to_print.txt
