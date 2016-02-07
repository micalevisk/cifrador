# !/bin/bash
for (( i=1,x=1,j=1; i<=36; i++,x++ ))
do
	echo "$j$x"
	if [ $x -eq 6 ]; then
		x=0
		((j++))
	fi
done
# [11, 12, 13, 14, 15, 16, 21, 22, 23, 24, 25, 26, 31, 32, 33, 34, 35, 36, 41, 42, 43, 44, 45, 46, 51, 52, 53, 54, 55, 56, 61, 62, 63, 64, 65, 66]

# Após esse loop, executar comando:
# $ grep --color -in '' "tabela_convertida/paginas/vetor1.original" | awk -F: '{print $2":"$1}' > vetor1
# E o arquivo entrará no formato PREFIXO:PÁGINA