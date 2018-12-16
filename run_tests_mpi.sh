#!/bin/bash

sc_util=$1
command=$2
side=$3
max_threads=$4
output_file=$5

for (( i = 0; i < 1; i++ ))
do
    for (( num_threads = 1; num_threads <= max_threads; num_threads *= 2 ))
    do
        ${sc_util} -n ${num_threads} -w 00:01:00 --stderr ${output_file} ${command} -- ${side} ${side} ${num_threads}
    done
done
