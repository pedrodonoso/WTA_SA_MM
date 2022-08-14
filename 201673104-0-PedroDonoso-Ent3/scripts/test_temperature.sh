#!/bin/bash

instances=( 5 10 20 30 40 50 60 70 80 90 100 200 ) 

for i in $(seq 0.90 0.01 0.99) ; do # coeficientes de decrecimiento
    for n in ${instances[@]} ; do
        for j in {1..5}; do
            make run INS=$n K=$i T_INIT=1000 T_FINISH=0.1 MAX_ITER=100000 MOVE=1
        done
    done
done