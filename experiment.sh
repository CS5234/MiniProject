#!/bin/bash

CODE_DIR=./code
DATA_DIR=./data
OUTP_DIR=./output
EXEC_DIR=./executables


# compilations
g++ $CODE_DIR/truth.cpp -w -o $EXEC_DIR/truth -O2
g++ $CODE_DIR/bfs_cache_efficient.cpp -w -o $EXEC_DIR/bfs-cache -O2
g++ $CODE_DIR/bfs_cache_efficient-2.cpp -w -o $EXEC_DIR/bfs-cache-2 -O2
g++ $CODE_DIR/seidel-armadillo.cpp -w -o $EXEC_DIR/seidel-armadillo -O2 -larmadillo

# ensure correctness
for data in $DATA_DIR/*; do
	echo "Experimenting on " $data
	printf "truth.cpp: "
	perf stat -e cache-references -e cache-misses -e instructions $EXEC_DIR/truth            < $data
	printf "bfs-cache.cpp: "
	perf stat -e cache-references -e cache-misses -e instructions $EXEC_DIR/bfs-cache        < $data
	printf "bfs-cache-2.cpp: "
	perf stat -e cache-references -e cache-misses -e instructions $EXEC_DIR/bfs-cache-2      < $data
	printf "seidel-armadillo.cpp: "
	perf stat -e cache-references -e cache-misses -e instructions $EXEC_DIR/seidel-armadillo < $data
	printf "\n"

	for out1 in $OUTP_DIR/*; do
		for out2 in $OUTP_DIR/*; do
			diff $out1 $out2
		done
	done
done

