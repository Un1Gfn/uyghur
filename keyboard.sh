#!/bin/bash -eu

# convert character to ascii
c2i() {
    printf %d "'$1'"
}

# convert ascii to character
i2c() {
    printf "\x$(printf %x "$1")"
}

# append to dict
a() {
    local i=$(c2i $1)
    K[$i]="$2"
}

# look up dict
K=()
q0() {
    local i="$(c2i $1)"
    local r="${K[i]}"
    printf %s "$r"
}

# convert
q() {
    local c
    local i
    for (( i=0; i<${#1}; i++ )); do
        c="${1:$i:1}"
        q0 "$c"
    done
}

# load
l() {
    a q $'\u0686' // چ
    a w $'\u06cb' // ۋ
    a e $'\u06d0' // ې
    a r $'\u0631' // ر
    a t $'\u062a' // ت
    a y $'\u064a' // ي
    a u $'\u06c7' // ۇ
    a i $'\u06ad' // ڭ
    a o $'\u0648' // و
    a p $'\u067e' // پ

    a a $'\u06be' // ھ
    a s $'\u0633' // س
    a d $'\u062f' // د 
    a f $'\u0627' // ا 
    a g $'\u06d5' // ە 
    a h $'\u0649' // ى 
    a j $'\u0642' // ق 
    a k $'\u0643' // ك 
    a l $'\u0644' // ل

    a z $'\u0632' // ز
    a x $'\u0634' // ش
    a c $'\u063a' // غ
    a v $'\u06c8' // ۈ
    a b $'\u0628' // ب
    a n $'\u0646' // ن
    a m $'\u0645' // م
    a / $'\u0626' // ئ 

    a D $'\u0698' // ژ
    a F $'\u0641' // ف
    a G $'\u06af' // گ
    a H $'\u062e' // خ
    a J $'\u062c' // ج
    a K $'\u06c6' // ۆ

}

e() {
    echo
}

main() {

    local i
    l

    #q "f"
    e
    #q "/fnf"
    e
    q "/g"
    e

    e
    #for i in {a..z}; do q "/$i"; e; done

    echo

}

main

