#!/bin/bash
# replace all local include header in some cpp, and open temp file with vim.
# set default include path with var: include_path.

include_path=$(realpath ~/git/icpc_lib/include)
output=
view=1

args=$(getopt -o o:i:q -n "$0" -- "$@")
if [ $? -ne 0 ]; then
	echo "opt preprocess error"
	exit 1
fi
eval set -- "$args"

for ((;;)); do
	case "$1" in
		-o)
			output="$2"
			shift
			;;
		-i)
			include_path="$2"
			shift
			;;
		-q)
			view=0
			;;
		--)
			break
			;;
		*)
			echo "opt $1 error*"
			exit 1
			;;
		?)
			echo "opt $1 error?"
			exit 1
			;;
	esac
	shift
done
shift

if [ $# -ne 1 ]; then
	echo "(file)"
	exit 1
fi
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

# delete already occured "xxx.h".
# (line, buf) -> (buf)
delete() {
	ret=$(
echo "$2" |
sed "
$1d
")
	echo "$ret"
}

declare -A filemap

# do...while
arr=($(search "$file"))
until [ ${#arr[*]} -eq 0 ]; do
	if [ ! -f $include_path/${arr[1]} ]; then
		echo "file ${arr[1]} not found in $include_path."
		exit 1
	fi
	if [[ ${filemap[${arr[1]}]} == "used" ]]; then
		echo "file ${arr[1]} occ again!"
		file=$(delete ${arr[0]} "$file")
	else
		file=$(replace ${arr[0]} ${arr[1]} "$file")
		filemap[${arr[1]}]="used"
	fi
	arr=($(search "$file"))
done

if [[ -z $output ]]; then
	output=$(mktemp tmp.XXX.cpp)
fi

echo "$file" > $output

if [ $view -eq 1 ]; then
	vim $output
	rm -f $output
fi

exit 0
