#!/bin/bash

TMPOUT=/tmp/css_test_out

# test oneline files - every line is separate test
ONELINES=tests/*.oneline
for ONELINE in $ONELINES
do
  echo "Processing $ONELINE file..."
  COUNT=1
  while read LINE
  do
      build/bin/CssPreprocessor <<< "$LINE" &> $TMPOUT
      if [ $? -eq 0 ]; then
          echo "Line $COUNT: PASSED"
      else
          echo "Line $COUNT: FAILED"
          echo "Input: $LINE"
          echo "Trace: "
          cat $TMPOUT
      fi
      COUNT=$((COUNT+1))
  done < $ONELINE
  echo "";
done
