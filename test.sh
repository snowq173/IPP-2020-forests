#!/bin/bash
a=0
b=0

prog=$1
dir=$2

for f in $dir/*.in

do
	if(valgrind --leak-check=full -q ./$prog <$f >myout.out 2>myerr.err && diff myout.out ${f%in}out >/dev/null && diff myerr.err ${f%in}err >/dev/null)
	then
		let "a += 1"
		echo "Test $f - OK"
	else
		echo "Test $f - WRONG"
	fi
	let "b += 1"
	rm myout.out
	rm myerr.err
done

echo "Correct/All: $a/$b"