#!/bin/bash

# Received help from Yeury Galvo

#create folder to hold the output files from your distributor
if [ ! -d /tmp/CSC412_prog04 ]; then
  mkdir -p /tmp/CSC412_prog04;
fi
# verify that the correct number of arguments was passed in
if [ "$#" = "2" ]
    then
        # check the process index of every file in the directory
        num_procs=0
        for fp in $(ls "$1")
        do
            # locate the process index in the file
            proc_index=$(grep -o '^[0-9]*' "$1/$fp")
            if [ $proc_index -gt $num_procs ];
            then
                # save the value that is largest
                num_procs=$proc_index
            fi
        done
    # + 1 because distributors start with 0
    distr=$( expr $num_procs + 1 )
    # give the executable, number of child processes,
    # the path to the directory, and the name of the .c file
    ../Source/Version01/exe/version01 $distr $1 $2
else
    echo "ERROR: not enough arguments"
    echo "Usage: $0 <path-to-directory> <filename>"
    exit
fi
