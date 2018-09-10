#!/bin/bash
# End 2 end test suite for toy_robot app testing


./test_e2e.sh test_files/test1.txt 3,3,NORTH
./test_e2e.sh test_files/test2.txt 0,0,WEST
./test_e2e.sh test_files/test3.txt 0,5,NORTH
./test_e2e.sh test_files/test4.txt 5,5,SOUTH
