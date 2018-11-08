#define ARMA_NO_DEBUG

#include <fstream>
#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

void Seidel(int n, imat& A) {
    bool done = true;
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < n; j++) 
            if (i != j && A(i,j) == 0) 
                done = false, i = j = n;

    if (done) 
        return;

    imat B = A * A;
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < n; j++) 
            if (i != j && (A(i,j) == 1 || B(i,j) > 0)) 
                B(i,j) = 1;
            else 
                B(i,j) = 0;

    Seidel(n, B);
    imat X = B * A;
    icolvec degree = sum(A, 1);
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < n; j++) 
            if (X(i,j) >= B(i,j) * degree[j])
                A(i,j) = 2 * B(i,j);
            else
                A(i,j) = 2 * B(i,j) - 1;
}

inline void read_input(int& n, int& m, imat& adjMat) {
	cin >> n >> m;
    adjMat = imat(n, n, fill::zeros);
    while (m--) {
        int u, v;
        cin >> u >> v;
        adjMat(u,v) = adjMat(v,u) = 1;
    }
}

inline double solve(int n, imat& adjMat) {
    clock_t start = clock();
    Seidel(n, adjMat);
    return (clock() - start) / (double) CLOCKS_PER_SEC;
}

inline void debug(int n, imat& adjMat) {
    ofstream os("../output/seidel-armadillo.out");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            os << adjMat(i,j) << " ";
        } os << "\n";
    }
}

int main() {

    int n, m;
    imat adjMat;

	read_input(n, m, adjMat);

	double duration = solve(n, adjMat);

#ifndef NDEBUG
	debug(n, adjMat);
#endif

    printf("%f\n", duration);

    return 0;
}