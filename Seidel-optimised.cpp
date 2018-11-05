#include <bits/stdc++.h>
using namespace std;

const int MAXN = 405;

int n, m;
int deg[MAXN], adjMat[MAXN][MAXN];

void multiply(const int A[MAXN][MAXN], const int B[MAXN][MAXN], int Z[MAXN][MAXN]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				Z[i][j] += A[i][k] + B[k][j];
			}
		}
	}
}

void Seidel(int A[MAXN][MAXN], int res[MAXN][MAXN]) {
	// multiply
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				res[i][j] += A[i][k] + A[j][k];
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j and (A[i][j] == 1 or res[i][j] > 0)) {
				res[i][j] = 1;
			} else {
				res[i][j] = 0;
			}
		}
	}

	bool done = true;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j && res[i][j] == 0) {
				done = false;
				break;
			}
		}
	}

	if (done) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				res[i][j] = 2 * res[i][j] - A[i][j];
			}
		}
		return;
	}

	int T[MAXN][MAXN]; memset(T, 0, sizeof(T));
	Seidel(res, T);

	memset(res, 0, sizeof(res));
	multiply(T, A, res);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (res[i][j] >= T[i][j] * deg[j]) {
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

	clock_t start = clock();
	Seidel(adjMat, res);

	double duration = (clock() - start) / (double) CLOCKS_PER_SEC;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", res[i][j]);
		} printf("\n");
	}

	printf("duration: %f\n", duration);

	return 0;
}