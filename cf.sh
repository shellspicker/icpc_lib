#!/bin/bash

if [ $# -ne 1 ]; then
	echo "(file)"
	exit 1
fi

file=$1

./replace.sh $file -q -ocf.cpp
g++ -ocf cf.cpp
