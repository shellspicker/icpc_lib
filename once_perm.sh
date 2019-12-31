#!/bin/bash
# arg1: totoal face num.
# just read single permutation(2 line), input the changed face
# output once trans status(and it's inverse).

num=$1
tmpfile=$(mktemp tmp.XXX)

awk '{
for (c = 1; c <= NF; ++c)
	if (NR == 1)
		p[c] = $c
	else
		p[c] = p[c]" "$c
}
END {
for (r = 1; p[r] != ""; ++r)
	print p[r]
}' |
awk -v dn=$num '{
c[$1]++
print $0
}
END {
for (d = 1; d <= dn; ++d)
	if (!c[d])
		print d,d
}' > $tmpfile

cat $tmpfile | sort -nk1 | awk '{printf "%2s ", $2} END {printf "\n"}'
cat $tmpfile | sort -nk2 | awk '{printf "%2s ", $1} END {printf "\n"}'

rm -f $tmpfile
