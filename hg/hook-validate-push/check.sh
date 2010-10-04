#!/bin/bash

TMP=`mktemp -u`
FAIL=0

# Don't panic, HG will use hardlinks for this
hg clone file://. $TMP > /dev/null 2>&1

for node in `hg log --template '{node}\n' -r $HG_NODE:`; do
    rm $TMP/* -fr
    hg -R $TMP revert --all -r $node > /dev/null 2>&1

    # Call here the real checker
    ./assertText.sh $TMP

    if [ "$?" -ne 0 ]; then
	echo "Assertion failed!"
	FAIL=1
	break
    fi
done

rm $TMP/ -fr
exit $FAIL






