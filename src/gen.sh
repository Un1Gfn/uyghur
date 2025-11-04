#!/bin/bash -eu

A=(
	26
	27 D5 28 7E 2A 2C 86 2E 2F 31 32 98 33 34 3A 41 42 43 AF AD 44 45 46 BE 48 C7 C6 C8 CB D0 49 4A
)
[ "33" = "${#A[@]}" ]
# hamza A[0]
# alphabet A[1] .. A[32]

V4=(1 2 25 26 27 28)
# V8

C2=(             9 10 11 12                                     29    )
C4=( 3 4 5 6 7 8            13 14 15 16 17 18 19 20 21 22 23 24    32 )

# initial
I=21

# final
F=1

f() {
	local i
	local j
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
	printf '/* %02d */ (LPA){ &(L){.s="' "$i"
}

# comma
c() {
	printf '",.l=NULL}, &(L){.s="'
}

# end
e() {
	echo '",.l=NULL}, NULL },'
}

header() { cat <<"EOF"
typedef struct {
	const char *s;
	const PangoLayout *l;
} L;

typedef L *LP;

typedef LP LPA[];
typedef LP *LPP;

LPP I[2][16] = {

EOF
}

group1() {
	# vowels except V8
	local i
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

f8() {
	b
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
}

# vowels of V8
group2() {
	local i
	printf "[0][0] = "
	i=30
	f8
	printf "[1][0] = "
	i=31
	f8
	printf "\n\n"
}

footer() {
	printf "};\n\n// ok\n\n"
}

main() {
	local i
	echo
	header
	paste -d "" \
			<(
				for i in 0 1; do
					printf "[$i][%s] = \n" {1..15}
				done
			) <(
					group1
			)
	echo
	group2
	footer
}

main; exit

