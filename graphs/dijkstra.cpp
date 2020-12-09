#include <bits/stdc++.h>
using namespace std;

#define INF 99999

struct edge
{
	int key;
	int weight;
	edge(int k, int w)
	{
		key = k;
		weight = w;
	}
};

vector<vector<edge>> graph;
vector<int> distances;

int dijkstra(int, int);

// given a bidirectional graph, return the shortest path from node A to B
int main()
{
	int amnt_nodes, amnt_edges;
	cin >> amnt_nodes >> amnt_edges;

	int start, end;
	cin >> start >> end;

	graph = vector<vector<edge>>(amnt_nodes + 1, vector<edge>());

	for (int i = 0; i < amnt_edges; i++)
	{
		int origin, end, distance;
		cin >> origin >> end >> distance;

		graph[origin].push_back(edge(end, distance));
		graph[end].push_back(edge(origin, distance));
	}

	distances = vector<int>(graph.size(), INF);
	cout << dijkstra(start, end);
}

struct node_has_shortest_path
{
	bool operator()(const pair<int, int> &a, const pair<int, int> &b) const
	{
		return a.second < b.second;
	}
};

int dijkstra(int start, int end)
{
	set<pair<int, int>, node_has_shortest_path> set_nodes = set<pair<int, int>, node_has_shortest_path>();

	set_nodes.insert(make_pair(start, 0));
	distances[start] = 0;

	while (!set_nodes.empty())
	{
		pair<int, int> node_info = *(set_nodes.begin());
		int node = node_info.first;
		int node_distance = node_info.second;
		set_nodes.erase(set_nodes.begin());
		if (node == end)
			return distances[node];

		for (edge cur_edge : graph[node])
		{
			int distance = node_distance + cur_edge.weight;
			if (distance < distances[cur_edge.key])
			{
				if (distances[cur_edge.key] == INF) //this is just an optimization
					set_nodes.erase(make_pair(cur_edge.key, distances[cur_edge.key]));
				distances[cur_edge.key] = distance;
				set_nodes.insert(make_pair(cur_edge.key, distance));
			}
		}
	}

	return -1;
}
