
#include <vector>
#include <iostream>
#include <queue> 
#include <algorithm>



using namespace std;

void insertV(vector<int> &v, int a) {
	v.push_back(a);
}

void constructAdjLst(vector<vector<int>> &adjLst, int m) {
	int a, b;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		insertV(adjLst.at(a), b);
		insertV(adjLst.at(b), a);
	}
}


void bfs(int i, vector<vector<int>> &adjLst, int** distance, int n) {
	int visited[n] = {0};
	queue<int> q;
	q.push(i);
	int d = 0;

	while (!q.empty()) {
		queue<int> nq;
		while (!q.empty()) {
			int next = q.front();
			visited[next] = 1;
			distance[i][next] = d;	
			q.pop();
			for (int k = 0; k < adjLst.at(next).size(); k++) {
				if (!visited[adjLst.at(next).at(k)]) {
					nq.push(adjLst.at(next).at(k));
				}
			}
		}
		q = nq;
		d++;
	}
}

void minus_difference(vector<int> &from, vector<int> &base) {
	int i = 0, j = 0;

	while (i < from.size() && j < base.size()) {
		if (from.at(i) == -1)
			continue;
		if (from.at(i) < base.at(j)) {
			i++;
		} else if (from.at(i) > base.at(j)) {
			j++;
		} else {
			from.at(i) = -1;
		}
	}
}

void removeDuplicates(vector<int> &vec) {
	int cur = vec.at(0);
	for (int i = 1; i < vec.size(); i++) {
		if (vec.at(i) == cur) {
			vec.at(i) = -1;
		} else {
			cur = vec.at(i);
		}
	}
}

void bfs_cache_efficient(int origin, vector<vector<int>> &adjLst, int** distance, int n) {
	vector<int> prev;
	prev.push_back(origin);

	vector<int> cur = adjLst.at(origin);
	sort(cur.begin(), cur.end());

	distance[origin][origin] = 0;
	for (int k = 0; k < cur.size(); k++) {
		distance[origin][cur.at(k)] = 1;
	}

	int depth = 2;

	while (cur.size() > 0) {
		vector<int> vec;

		for (int i = 0; i < cur.size(); i++) {
			for (int j = 0; j < adjLst.at(cur.at(i)).size(); j++) {
				vec.push_back(adjLst.at(cur.at(i)).at(j));
			}
		}
		sort(vec.begin(), vec.end());
		removeDuplicates(vec);

		minus_difference(vec, prev);
		minus_difference(vec, cur);

		vector<int> next;
		for (int i = 0; i < next.size(); i++) {
			if (vec.at(i) != -1) {
				next.push_back(vec.at(i));
			}
		}
		for (int i = 0; i < next.size(); i++)
			distance[origin][next.at(i)] = depth;
		depth++;
		prev = cur;
		cur = next;
	}
}


int main() {
	int n, m;
	cin >> n >> m;

	vector<vector<int>> adjLst;
	adjLst.resize(n);

	constructAdjLst(adjLst, m);

	int** distance = new int*[n];
	for (int i = 0; i < n; i++) 
		distance[i] = new int[n];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			distance[i][j] = -1;
		}
	}

	clock_t start = clock();
	for (int i = 0; i < n; i++)
		bfs(i, adjLst, distance, n);

	double duration = (clock() - start) / (double) CLOCKS_PER_SEC;

	cout << "duration: " << duration << "\n";

	// for (int i = 0; i < n; i++) {
	// 	for (int j = 0; j < n; j++) {
	// 		cout << distance[i][j] << " ";
	// 	}
	// 	cout << "\n";
	// }

	for (int i = 0; i < n; i++)
		delete[] distance[i];
	delete[] distance;
}