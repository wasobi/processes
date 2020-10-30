#!/bin/bash

# Program File
PROG_PATH_1="../Source/Version01/exe/version01"
PROG_PATH_2="../Source/Version02/exe/version02"

# Version 1
gcc -Wall ../Source/Version01/src/main.c ../Source/Version01/src/startup.c ../Source/Version01/src/dispatcher.c ../Source/Version01/src/distributor.c ../Source/Version01/src/data_processing.c -o $PROG_PATH_1

# # Version 2
# gcc -Wall ../Source/Version02/src/main.c ../Source/Version02/src/startup.c ../Source/Version02/src/dispatcher.c ../Source/Version02/src/distributor.c ../Source/Version02/src/data_processing.c -o $PROG_PATH_2
