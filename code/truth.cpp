#include <queue>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

inline void read_input(int& n, int& m, vector<vector<int>>& adjList) {
	cin >> n >> m;
	adjList.assign(n, vector<int>());{
		while (m--) {
			int u, v;
			cin >> u >> v;
			adjList[u].push_back(v);
			adjList[v].push_back(u);
		}
	}
}
	
inline double solve(int n, int m, vector<vector<int>>& adjList, vector<vector<int>>& res) {
	clock_t start = clock();
	res.assign(n, vector<int>(n, -1));
	for (int i = 0; i < n; i++) {
		queue<int> q; q.push(i); res[i][i] = 0;
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int v : adjList[u]) {
				if (res[i][v] == -1) {
					q.push(v); res[i][v] = res[i][u] + 1;
				}
			}
		}
	}
	return (clock() - start) / (double) CLOCKS_PER_SEC;
}

inline void debug(int n, vector<vector<int>> res) {
	ofstream os("../output/truth.out");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			os << res[i][j] << " ";
		} os << "\n";
	}
}

int main() {

	int n, m;
	vector<vector<int>> adjList;

	read_input(n, m, adjList);

	vector<vector<int>> res;
	double duration = solve(n, m, adjList, res);

#ifndef NDEBUG
	debug(n, res);
#endif

	printf("duration: %f\n", duration);

	return 0;
}