#!/bin/bash

command=$1
max_threads=$2
output_file=$3

for (( i = 0; i < 3; i++ ))
do
    # rows < cols
    for (( rows = 1000, cols = 3000; cols < 70000; rows += 4000, cols += 12000 ))
    do
        for (( num_threads = 1; num_threads <= max_threads; num_threads *= 2 ))
        do
            bsub -n ${num_threads} -W 1 -e ${output_file} ${command} ${rows} ${cols} ${num_threads}
        done
    done

    # rows > cols
    for (( rows = 3000, cols = 1000; rows < 70000; rows += 12000, cols += 4000 ))
    do
        for (( num_threads = 1; num_threads <= max_threads; num_threads *= 2 ))
        do
            bsub -n ${num_threads} -W 1 -e ${output_file} ${command} ${rows} ${cols} ${num_threads}
        done
    done

    # rows == cols
    for (( rows = 3000, cols = 3000; cols < 70000; rows += 12000, cols += 12000 ))
    do
        for (( num_threads = 1; num_threads <= max_threads; num_threads *= 2 ))
        do
            bsub -n ${num_threads} -W 1 -e ${output_file} ${command} ${rows} ${cols} ${num_threads}
        done
    done
done
