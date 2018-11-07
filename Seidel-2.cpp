#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n, m;
int adjMat[MAXN][MAXN];

void multiply(const int A[MAXN][MAXN], const int B[MAXN][MAXN], int Z[MAXN][MAXN]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				Z[i][j] += A[i][k] * B[j][k];
			}
		}
	}
}

void print(const int A[MAXN][MAXN]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", A[i][j]);
		} printf("\n");
	}
}

void Seidel(int A[MAXN][MAXN]) {
	//printf("A\n");
	//print(A);

	bool done = true;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) {
				continue;
			}

			if (A[i][j] == 0) {
				done = false;
				break;
			}
		}
		if (!done) {
			break;
		}
	}

	if (done) {
		return;
	}

	int B[MAXN][MAXN]; memset(B, 0, sizeof(B));
	multiply(A, A, B);

	// printf("Z:\n");
	// print(Z);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j && (A[i][j] == 1 || B[i][j] > 0)) {
				B[i][j] = 1;
			} else {
				B[i][j] = 0;
			}
		}
	}

	// printf("B:\n");
	// print(B);

	// int T[MAXN][MAXN]; memset(T, 0, sizeof(T));
	Seidel(B);

	// printf("T:\n");
	// print(T);

	int X[MAXN][MAXN]; memset(X, 0, sizeof(X));
	multiply(B, A, X);

	// printf("X:\n");
	// print(X);

	int degree[MAXN];
	//printf("degree:\n");
	for (int i = 0; i < n; i++) {
		degree[i] = 0;
		for (int j = 0; j < n; j++) {
			degree[i] += A[i][j];
		}
	//	printf("%d ", degree[i]);
	} //printf("\n");

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (X[i][j] >= B[i][j] * degree[j]) {
				A[i][j] = 2 * B[i][j];
			} else {
				A[i][j] = 2 * B[i][j] - 1;
			}
		}
	}

	// printf("RES:\n");
	// print(res);
}

int main() {

	cin >> n >> m;
	while (m--) {
		int u, v;
		cin >> u >> v;

		adjMat[u][v] = adjMat[v][u] = 1;
	}

	clock_t start = clock();
	printf("Going to Seidel\n");
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