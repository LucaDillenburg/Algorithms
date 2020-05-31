#include <bits/stdc++.h>
using namespace std;

int seen[1005];
vector<vector<int>> graph;

int dfs(int);

// given a directional graph, return the longest path from node 1
int main() {
	int amnt_nodes, amnt_edges;
	cin >> amnt_nodes >> amnt_edges;

	graph = vector<vector<int>>(amnt_nodes+1);
	for (int i=0; i<=amnt_nodes; i++)
		graph[i] = vector<int>();

	for (int i=0; i<amnt_edges; i++) {
		int origin, end;
		cin >> origin >> end;
		graph[origin].push_back(end);
	}

	cout << dfs(1);
}

int dfs(int node) {
	int greatest_path = 0;
	for (int end : graph[node]) {
		if (seen[end])
			return -1;
		seen[end] = true;

		int greatest_path_cur = dfs(end);
		if (greatest_path_cur < 0)
			return greatest_path_cur;

		greatest_path = max(greatest_path_cur + 1, greatest_path);
	}
	return greatest_path;
}
