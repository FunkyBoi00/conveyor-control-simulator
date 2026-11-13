#!/bin/bash

./build/conveyor < tests/scenarios/pause.txt > build/pause-output.txt
result=$?

if [ "$result" -ne 0 ]; then
     echo "ERROR: simulator execution failed" >&2
     exit 2
fi

grep "State:" build/pause-output.txt > build/pause-actual.txt
result=$?

if [ "$result" -ne 0 ]; then
     echo "ERROR: could not extract states" >&2
     exit 2
fi

diff -u tests/expected/pause.txt build/pause-actual.txt
result=$?

if [ "$result" -eq 0 ]; then
     echo "PASS: pause scenario"
     exit 0
elif [ "$result" -eq 1 ]; then
     echo "FAIL: unexpected states"
     exit 1
else
     echo "ERROR: comparison failed" >&2
     exit 2
fi
