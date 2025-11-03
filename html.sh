#!/bin/bash -eu

H=/tmp/x.html

#V=(1 2 25 26 27 28 30 31)
#C=(3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 29 32)
A=(00 27 D5 28 7E 2A 2C 86 2E 2F 31 32 98 33 34 3A 41 42 43 AF AD 44 45 46 BE 48 C7 C6 C8 CB D0 49)
A+=(26 40)
[[ "34" == "${#A[@]}" ]]

V4=(1 2 25 26 27 28)
V8=(30 31)

C2=(             9 10 11 12                                     29    )
C4=( 3 4 5 6 7 8            13 14 15 16 17 18 19 20 21 22 23 24    32 )

f() {
	for i in "$@"; do
		j="${A["$i"]}"
		echo -ne "\u06$j"
	done
}

# grey
g() {
	echo -n "<span style=color:#EEEEEE>$(f "$@")</span>"
}

# space
s() {
	printf " "
}

echo

{ cat <<EOF
<html>
<head>
<meta charset="UTF-8">
</head>
<body>
<pre style='font-family:"Noto Serif Old Uyghur";'>
EOF
printf "\n"

	# V4
	for i in "${V4[@]}"; do
		printf "$i - "
		f 32 "$i"
		printf " "
		f "$i"
		printf " "
		g 21
		f "$i"
		printf " "
		g 21
		f 32 "$i"
		echo
	done
	printf "\n"

	# V8
	for i in "${V8[@]}"; do
	#for i in 31; do
		printf "$i - "
		f 32 $i
		s
		f $i
		s
		f 32 $i; g 1
		s
		f $i; g 21
		s
		g 21; f $i; g 1
		s
		g 21; f 32 $i; g 1
		s
		g 21; f $i
		s
		g 21; f 32 $i
		printf " "
		echo
	done
	printf "\n"

	# C2
	for i in "${C2[@]}"; do
		printf "$i - "
		s
		f $i
		s
		g 21; f $i
		s
		echo
	done
	echo

	# C3

	# C4
	for i in "${C4[@]}"; do
		printf "$i - "
		s
		f $i
		s
		f $i; g 1
		s
		g 21; f $i; g 1
		s
		g 21; f $i
		s
		echo
	done
	echo

	# alphabet listing
	for i in {1..32}; do
		printf "$i - "
		f "$i"
		echo
	done
	echo

echo "<""/pre></html>"; } | tee /tmp/x.html

printf "\nw $H\n\n"

