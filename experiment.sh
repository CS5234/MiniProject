#!/bin/bash

CODE_DIR=./code
DATA_DIR=./data
OUTP_DIR=./output
EXEC_DIR=./executables


# compilations
g++ $CODE_DIR/truth.cpp -w -o $EXEC_DIR/truth -O2
g++ $CODE_DIR/seidel-armadillo.cpp -w -o $EXEC_DIR/seidel-armadillo -O2 -larmadillo

# ensure correctness
for data in $DATA_DIR/*; do
	echo "Experimenting on " $data
	printf "truth.cpp: "
	$EXEC_DIR/truth            < $data
	printf "seidel-armadillo.cpp: "
	$EXEC_DIR/seidel-armadillo < $data
	echo
done

diff $OUTP_DIR/truth.out $OUTP_DIR/seidel-armadillo.out