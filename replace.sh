#!/bin/bash
# replace all local include header in some cpp, and open temp file with vim.
# set default include path with var: include_path.

if [ $# -ne 1 ]; then
	echo "(file)"
	exit 1
fi

include_path=$(realpath ~/git/icpc_lib/include)
file=$(cat $1)

# search include "xxx.h", return match line and xxx.h.
# (file) -> (line, file).
search() {
	ret=$(
echo "$1" |
sed -n "
/include \"/{
=
s/^.*\"\\(.*\\)\"/\\1/p
q}
")
	echo "$ret"
}
# replace include "xxx.h" line to xxx.h, and delete this line.
# (line, file, buf) -> (buf).
replace() {
	ret=$(
echo "$3" |
sed "
$1r $include_path/$2
$1d
")
	echo "$ret"
}

arr=($(search "$file"))
until [ ${#arr[*]} -eq 0 ]; do
	file=$(replace ${arr[0]} ${arr[1]} "$file")
	arr=($(search "$file"))
done
output=$(mktemp tmp.XXX.cpp)
echo "$file" > $output
vim $output
rm -f $output

exit 0
