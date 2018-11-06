#include <ctime>
#include <queue>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 10005;

int n, m, u, v, dist[MAXN][MAXN];
vector<int> adjList[MAXN];

void minus_difference(vector<int> &from, vector<int> &base) {
	int i = 0, j = 0;

	while (i < from.size() && j < base.size()) {
		if (from.at(i) == -1) {
			i++;
		} else if (from.at(i) < base.at(j)) {
			i++;
		} else if (from.at(i) > base.at(j)) {
			j++;
		} else {
			from.at(i) = -1;
			i++;
			j++;
		}
	}
}

void removeDuplicates(vector<int> &vec) {
	if (vec.size() == 0) 
		return;
	int cur = vec.at(0);
	for (int i = 1; i < vec.size(); i++) {
		if (vec.at(i) == cur) {
			vec.at(i) = -1;
		} else {
			cur = vec.at(i);
		}
	}
}

void printVec(vector<int> &vec) {
	if (vec.size() == 0) {
		cout << "vec empty\n";
		return;
	}

	cout << "vec: ";
	for (int i = 0; i < vec.size(); i++) {
		cout << vec.at(i) << " ";
	}
	cout << "\n";
}

void bfs_cache_efficient(int origin) {
	vector<int> prev;
	prev.push_back(origin);

	vector<int> cur = adjList[origin];

	dist[origin][origin] = 0;
	for (int k = 0; k < cur.size(); k++) {
		dist[origin][cur[k]] = 1;
	}

	int depth = 2;

	while (cur.size() > 0) {
		vector<vector<int>> v;

		for (int i = 0; i < cur.size(); i++) {
			v.push_back(adjList[cur[i]]);
		}

		queue<int> q;
		for (int i = 0; i < cur.size(); i++) {
			q.push(i);
		}

		while (q.size() > 1) {
			int l = q.front(); q.pop();
			int r = q.front(); q.pop();

	        int i = v[l].size() - 1, j = v[r].size() - 1; int tar = i + j + 1;
	        v[l].resize(tar + 1);
	        while (j >= 0) {
	            v[l][tar--] = (i >= 0 && v[l][i] > v[r][j] ? v[l][i--] : v[r][j--]);
	        }

			q.push(l);
		}

		int f = q.front();

		removeDuplicates(v[f]);

		minus_difference(v[f], prev);
		minus_difference(v[f], cur);

		vector<int> next;
		for (int i = 0; i < v[f].size(); i++) {
			if (v[f][i] != -1) {
				next.push_back(v[f][i]);
			}
		}

		for (int i = 0; i < next.size(); i++)
			dist[origin][next[i]] = depth;

		depth++;
		prev = cur;
		cur = next;
	}
}


int main() {

	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		cin >> u >> v;
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}

	memset(dist, -1, sizeof(dist));

	clock_t start = clock();

	for (int i = 0; i < n; i++) {
		sort(adjList[i].begin(), adjList[i].end());
	}

	for (int i = 0; i < n; i++) {
		bfs_cache_efficient(i);
	}

	double duration = (clock() - start) / (double) CLOCKS_PER_SEC;

	cout << "duration: " << duration << "\n";

	// for (int i = 0; i < n; i++) {
	// 	for (int j = 0; j < n; j++) {
	// 		cout << dist[i][j] << " ";
	// 	}
	// 	cout << "\n";
	// }
}