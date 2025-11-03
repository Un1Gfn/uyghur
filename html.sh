#!/bin/bash -eu

H=/tmp/x.html

A=(00 27 D5 28 7E 2A 2C 86 2E 2F 31 32 98 33 34 3A 41 42 43 AF AD 44 45 46 BE 48 C7 C6 C8 CB D0 49 4A)
[[ "33" == "${#A[@]}" ]]

V=(1 2 25 26 27 28 30 31)
C=(3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 29 32)

#V4=(1 2 25 26 27 28)
#V6=(30 31)
#V=
#
#C3=(                                                        24
#C2=(            9 10 11 12                                     29
#C4=(3 4 5 6 7 8            13 14 15 16 17 18 19 20 21 22 23       32

g() {
	for i in "$@"; do
		j="${A["$i"]}"
		echo -ne "\u06$j"
	done
}

echo

{
cat <<EOF
<html>
<head>
<meta charset="UTF-8">
</head>
<body>
<pre style='font-family:"Noto Serif Old Uyghur";'>
EOF
printf "\n"
for i in "${V[@]}"; do
	g "$i"
	printf " "
done
printf "\n\n"
for i in "${V[@]}"; do
	printf "$i = "
	g 32 "$i"
	printf " "
	g "$i"
	printf " "
	g 21 "$i"
	printf " "
	g 21 32 "$i"
	echo
done
printf "\n"
for i in "${C[@]}"; do
	g "$i"
	printf " "
done
printf "\n\n"
echo "<""/pre></html>"
} | tee /tmp/x.html

printf "\nw $H\n\n"

