#!/bin/bash

if [ $# -ne 1 ]; then
	echo "(file)"
	exit 1
fi

file=$1
prepend=/home/zgh/git/icpc_lib

$prepend/replace.sh $file -q -otest.cpp
g++ -Wall -otest test.cpp
