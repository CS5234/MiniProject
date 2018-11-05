#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n, m;
int deg[MAXN], adjMat[MAXN][MAXN];

void multiply(const int A[MAXN][MAXN], const int B[MAXN][MAXN], int Z[MAXN][MAXN]) {
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			swap(B[i][j], B[j][i]);
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				Z[i][j] += A[i][k] + B[j][k];
			}
		}
	}
}

void Seidel(const int A[MAXN][MAXN], int res[MAXN][MAXN]) {
	int Z[MAXN][MAXN]; memset(Z, 0, sizeof(Z));
	multiply(A, A, Z);

	int B[MAXN][MAXN];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j and (A[i][j] == 1 or Z[i][j] > 0)) {
				B[i][j] = 1;
			} else {
				B[i][j] = 0;
			}
		}
	}

	bool done = true;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j && B[i][j] == 0) {
				done = false;
				break;
			}
		}
	}

	if (done) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				res[i][j] = 2 * B[i][j] - A[i][j];
			}
		}
		return;
	}

	int T[MAXN][MAXN]; memset(T, 0, sizeof(T));
	Seidel(B, T);

	int X[MAXN][MAXN]; memset(X, 0, sizeof(X));
	multiply(T, A, X);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (X[i][j] >= T[i][j] * deg[j]) {
				res[i][j] = 2 * T[i][j];
			} else {
				res[i][j] = 2 * T[i][j] - 1;
			}
		}
	}
}

int main() {

	cin >> n >> m;
	while (m--) {
		int u, v;
		cin >> u >> v;

		deg[u]++; deg[v]++;
		adjMat[u][v] = adjMat[v][u] = 1;
	}

	int res[MAXN][MAXN];
	Seidel(adjMat, res);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", res[i][j]);
		} printf("\n");
	}

	return 0;
}