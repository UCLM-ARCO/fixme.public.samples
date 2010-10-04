#!/bin/bash

for i in `find $1 -type f \! -path "*/.*"`; do
    file $i | grep 'text' > /dev/null 2>&1
    if [ "$?" -ne 0 ]; then
	echo "$i is not a text file!"
	exit 1
    fi
done
exit 0
