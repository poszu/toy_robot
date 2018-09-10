#!/bin/bash
# Tests toy_robot end 2 end
# It feeds toy_robot app from a file and verifies output
# Usage:
# ./test_e2e.sh <FILE WITH COMMANDS> <EXPECTED STDOUT>

# Compare two strings
function compare {
    if [ "$1" = "$2" ]; then
        echo PASS
    else
        echo FAIL
    fi
}

./../toy_robot -f $1 > tmp.txt
compare `cat tmp.txt` $2
rm tmp.txt
