#include <bits/stdc++.h>
using namespace std;

int n, m;

vector<int> degree;
vector<vector<int>> adjMat;

vector<vector<int>> X;

inline void multiply(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& Z) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Z[i][j] = 0;
            for (int k = 0; k < n; k++) {
                Z[i][j] += A[i][k] * B[j][k];
            }
        }
    }
}

void Seidel(vector<vector<int>>& A) {
    bool done = true;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                continue;
            }

            if (A[i][j] == 0) {
                done = false;
                i = j = n;  // break
            }
        }
    }

    if (done) {
        return;
    }

    vector<vector<int>> B(n, vector<int>(n, 0));
    multiply(A, A, B);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && (A[i][j] == 1 || B[i][j] > 0)) {
                B[i][j] = 1;
            } else {
                B[i][j] = 0;
            }
        }
    }

    Seidel(B);

    multiply(B, A, X);

    for (int i = 0; i < n; i++) {
        degree[i] = 0;
        for (int j = 0; j < n; j++) {
            degree[i] += A[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (X[i][j] >= B[i][j] * degree[j]) {
                A[i][j] = 2 * B[i][j];
            } else {
                A[i][j] = 2 * B[i][j] - 1;
            }
        }
    }
}

int main() {

    cin >> n >> m;
    
    adjMat.assign(n, vector<int>(n, 0));
    while (m--) {
        int u, v;
        cin >> u >> v;

        adjMat[u][v] = adjMat[v][u] = 1;
    }

    clock_t start = clock();

    X.assign(n, vector<int>(n, 0));
    degree.assign(n, 0);

    Seidel(adjMat);

    double duration = (clock() - start) / (double) CLOCKS_PER_SEC;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", adjMat[i][j]);
        } printf("\n");
    }

    printf("duration: %f\n", duration);

    return 0;
}