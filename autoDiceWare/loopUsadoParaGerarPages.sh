# !/bin/bash
for (( i=1,x=1,j=1; i<=36; i++,x++ ))
do
	echo "grep \"$j$x\" '$i' | cut -c 3- > pages/$i"
	if [ $x -eq 6 ]; then
		x=0
		((j++))
	fi
done