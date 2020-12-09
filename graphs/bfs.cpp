#include <bits/stdc++.h>
using namespace std;

int seen[1005];
vector<vector<int>> graph;

int bfs(int, int);

// given a directional graph, return the shortest path from node A to B
int main() {
	int amnt_nodes, amnt_edges;
	cin >> amnt_nodes >> amnt_edges;

	int a, b;
	cin >> a >> b;

	graph = vector<vector<int>>(amnt_nodes + 1);
	for (int i=0; i<=amnt_nodes; i++)
		graph[i] = vector<int>();

	for (int i=0; i<amnt_edges; i++) {
		int origin, end;
		cin >> origin >> end;
		graph[origin].push_back(end);
	}


	cout << bfs(a, b);
}

int bfs(int origin, int end) {
	queue<pair<int,int>> queue_cur_nodes = queue<pair<int,int>>();
	queue_cur_nodes.push(make_pair(origin,0));

	while (!queue_cur_nodes.empty()) {
		pair<int,int> cur_pair = queue_cur_nodes.front();
		queue_cur_nodes.pop();

		if (seen[cur_pair.first])
			continue;
		seen[cur_pair.first] = true;

		if (cur_pair.first == end)
			return cur_pair.second;
		for (int end_node : graph[cur_pair.first])
			queue_cur_nodes.push(make_pair(end_node, cur_pair.second+1));
	}

	return -1;
}
