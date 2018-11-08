#!/bin/bash

CODE_DIR=./code/
DATA_DIR=./data/
OUTP_DIR=./output/
EXEC_DIR=./executables/


# compilations
g++ $CODE_DIR/truth.cpp -w -o $EXEC_DIR/truth -O2
g++ $CODE_DIR/seidel-armadillo.cpp -w -o $EXEC_DIR/seidel-armadillo -O2 -larmadillo

# ensure correctness
echo "Running truth"
$EXEC_DIR/truth            < $DATA_DIR/graph-1000-200000.in
echo "Running seidel-armadillo"
$EXEC_DIR/seidel-armadillo < $DATA_DIR/graph-1000-200000.in

diff $OUTP_DIR/truth.out $OUTP_DIR/seidel-armadillo.out