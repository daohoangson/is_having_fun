#!/bin/bash

DIFF=`diff <(php main.php example.inp) <(cat example.out)`
if [ "x$DIFF" = "x" ]; then
	echo 'Looks good!'
fi
