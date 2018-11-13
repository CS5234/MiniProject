#define ARMA_NO_DEBUG

#include <cstdio>
#include <armadillo>

using namespace std;
using namespace arma;

int n, m;

void Seidel(imat& A) {
    bool done = true;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                continue;
            }

            if (A(i,j) == 0) {
                done = false;
                i = j = n;  // break
            }
        }
    }

    if (done) {
        return;
    }

    imat B = A * A;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && (A(i,j) == 1 || B(i,j) > 0)) {
                B(i,j) = 1;
            } else {
                B(i,j) = 0;
            }
        }
    }

    Seidel(B);

    imat X = B * A;

    icolvec degree = sum(A, 1);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (X(i,j) >= B(i,j) * degree[j]) {
                A(i,j) = 2 * B(i,j);
            } else {
                A(i,j) = 2 * B(i,j) - 1;
            }
        }
    }
}

inline void read_input() {
	scanf("%d%d", &n, &m);
	    
    imat adjMat = imat(n, n, fill::zeros);
    while (m--) {
        int u, v;
        scanf("%d%d", &u, &v);

        adjMat(u,v) = adjMat(v,u) = 1;
    }
}

inline double solve() {
    clock_t start = clock();

    Seidel(adjMat);

    return (clock() - start) / (double) CLOCKS_PER_SEC;
}

inline void debug() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%lld ", adjMat(i,j));
        } printf("\n");
    }
}

int main() {

	read_input();

	double duration = solve();

#ifndef DEBUG
	debug();
#endif

    printf("duration: %f\n", duration);

    return 0;
}