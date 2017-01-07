#!/bin/bash

DIFF=`diff <(g++ main.cpp && ./a.out < example.inp) <(cat example.out)`
if [ "x$DIFF" = "x" ]; then
	echo 'Looks good!'
fi
