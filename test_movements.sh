#!/bin/bash

instances=( 5 10 20 30 40 50 60 70 80 90 100 200 ) 
movements=( 0 1 2 )

for i in ${movements[@]} ; do
    for n in ${instances[@]} ; do
        for j in {1..10}; do
            make run INS=$n K=0.98 T_INIT=1000 T_FINISH=0.1 MAX_ITER=100000 MOVE=$i
        done;
    done
done