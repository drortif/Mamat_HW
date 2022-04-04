#!/bin/bash


> results.csv
> final_result.txt
> result.txt
> temp_result.txt

wget -O list.txt https://www.ynetnews.com/category/3082
cat list.txt | egrep -o https://www.ynetnews.com/article/......... > links.txt

sort links.txt | uniq -c | grep -o https://www.ynetnews.com/article/......... > unique_links.txt

links=$(cat $"unique_links.txt")

for LINE in $links; do echo ", Bennett," >> temp_result.txt; done

paste unique_links.txt temp_result.txt >> result.txt
> temp_result.txt

links=$(cat $"unique_links.txt")

for LINE in $links; do wget -O temp.txt "$LINE" | grep -o Bennett temp.txt | wc -l >> temp_result.txt; done

paste result.txt temp_result.txt >> final_result.txt

> result.txt
> temp_result.txt

links=$(cat $"unique_links.txt")

for LINE in $links; do echo -e ", Netanyahu," >> temp_result.txt; done

paste final_result.txt temp_result.txt >> result.txt

> final_result.txt
> temp_result.txt

links=$(cat $"unique_links.txt")

for LINE in $links; do wget -O temp.txt "$LINE" | grep -o Netanyahu temp.txt | wc -l >> temp_result.txt; done

paste result.txt temp_result.txt >> final_result.txt

sed -i 's/[[:space:]],/,/' final_result.txt
sed -i 's/[[:blank:]],/,/' final_result.txt
sed -i 's/[[:space:]]Bennett,[[:space:]]0,[[:space:]]Netanyahu,[[:space:]]0/-/' final_result.txt

cat final_result.txt | wc -l > num_of_lines.txt

cat final_result.txt >> num_of_lines.txt

cat num_of_lines.txt > final_result.txt

cat final_result.txt >> results.csv
