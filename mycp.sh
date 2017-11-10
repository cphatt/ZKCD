#! /bin/sh
	diff $1 $2
	if [ 0 -ne $? ];then
		cp $1 $2
	fi
