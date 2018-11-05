#include <bits/stdc++.h>
using namespace std;

const int MAXN = 305;

int n, m, u, v, res[MAXN][MAXN];
vector<int> adjList[MAXN];

int main() {

	cin >> n >> m;
	while (m--) {
		cin >> u >> v;

		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}

	clock_t start = clock();

	memset(res, -1, sizeof(res));

	for (int i = 0; i < n; i++) {
		queue<int> q; q.push(i); res[i][i] = 0;
		while (!q.empty()) {
			u = q.front(); q.pop();
			for (int v : adjList[u]) {
				if (res[i][v] == -1) {
					q.push(v); res[i][v] = res[i][u] + 1;
				}
			}
		}
	}
	
	double duration = (clock() - start) / (double) CLOCKS_PER_SEC;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", res[i][j]);
		} printf("\n");
	}

	printf("duration: %f\n", duration);

	return 0;
}