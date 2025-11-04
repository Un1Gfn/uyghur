#!/bin/bash -eu

A=(
	26
	27 D5 28 7E 2A 2C 86 2E 2F 31 32 98 33 34 3A 41 42 43 AF AD 44 45 46 BE 48 C7 C6 C8 CB D0 49 4A
)
[ "33" = "${#A[@]}" ]
# hamza A[0]
# alphabet A[1] .. A[32]

V4=(1 2 25 26 27 28)
V8=(30 31)

C2=(             9 10 11 12                                     29    )
C4=( 3 4 5 6 7 8            13 14 15 16 17 18 19 20 21 22 23 24    32 )

# initial
I=21

# final
F=1

f() {
	for i in "$@"; do
		j="${A["$i"]}"
		echo -n "\u06$j"
	done
}

g() {
	f "$@"
}

# begin
b() {
	printf "/* %02d */ { " "$i"
}

# comma
c() {
	printf '", "'
}

# end
e() {
	echo '", NULL };'
}

group1() {
	# vowels except V8
	for i in "${V4[@]}"; do
		b "$i"
		f 0 "$i"
		c
		f "$i"
		c
		g $I
		f "$i"
		c
		g $I
		f 0 "$i"
		e
	done
	# consonants
	{
		# C2
		for i in "${C2[@]}"; do
			b "$i"
			f $i
			c
			g $I; f $i
			e
		done
		# C4
		for i in "${C4[@]}"; do
			b "$i"
			f $i
			c
			f $i; g $F
			c
			g $I; f $i; g $F
			c
			g $I; f $i
			e
		done
	} | sort -n
}

# vowels of V8
group2() {
	for i in "${V8[@]}"; do
	#for i in 31; do
		b "$i"
		f 0 $i
		c
		f $i
		c
		f 0 $i; g $F
		c
		f $i; g $I
		c
		g $I; f $i; g $F
		c
		g $I; f 0 $i; g $F
		c
		g $I; f $i
		c
		g $I; f 0 $i
		e
	done
}

main() {
	echo
	paste -d "" \
		<(
			printf "R[%s] = \n" {1..16}
			printf "L[%s] = \n" {1..16}
		) <(
			group1
		)
	echo
	group2
	printf "\nOK\n\n"
}

main; exit

