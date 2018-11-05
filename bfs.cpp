
#include <vector>
#include <iostream>
#include <queue> 


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

void removeDuplicates(vector<int> &from, vector<int> &base) {

}

void bfs_cache_efficient(int i, vector<vector<int>> &adjLst, int** distance, int n) {
	vector<int> prev;
	prev.push_back(i);

	vector<int> cur = adjLst.at(i);
	sort(cur.begin(), cur.end());

	while (cur.size() > 0) {
		vector<int> vec;

		for (int i = 0; i < cur.size(); i++) {
			for (int j = 0; j < adjLst.at(cur.at(i)).size(); j++) {
				vec.push_back(adjLst.at(cur.at(i)).at(j));
			}
		}

		sort(vec.begin(), vec.end());
		vec.erase(unique(vec.begin(), vec.end()), vec.end());

		removeDuplicates(vec, prev);
		removeDuplicates(vec, cur);

		prev = cur;
		cur = vec;
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