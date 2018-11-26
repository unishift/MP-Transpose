#!/bin/bash

command=$1
side=$2
max_threads=$3
output_file=$4

for (( i = 0; i < 5; i++ ))
do
    for (( num_threads = 1; num_threads <= max_threads; num_threads *= 2 ))
    do
        bsub -n ${num_threads} -W 1 -e ${output_file} ${command} ${side} ${side} ${num_threads}
    done
done
