cp des_output.txt des_output_101.txt
sed -i '1,53d' des_output_101.txt
sed -i '/Slowly, a new text starts appearing on the screen. It reads .../d' des_output_101.txt
sed -i '/Press c to continue> /d' des_output_101.txt
sed -i '/The text in the screen vanishes!/d' des_output_101.txt
sed -i '/>/d' des_output_101.txt
sed -i '/^$/d' des_output_101.txt
sed -i 's/[[:blank:]]//g' des_output_101.txt 
head -n -10 des_output_101.txt > des_clean_output.txt
wc -l des_clean_output.txt
rm des_output_101.txt
