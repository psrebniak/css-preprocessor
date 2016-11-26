#!/bin/sh
cd $1
OUT=$(echo $2 | sed 's/\.in/\.out/' )
./CssPreprocessor -f $2 2> /dev/null | diff  --ignore-trailing-space --unified ${OUT} -

exit $?
