#include <bits/stdc++.h>
using namespace std;

struct path_info
{
	pair<int, int> v_path_in_root = {0, 0};
	pair<int, int> v_path_below = {0, 0};
};

path_info longest_path(const vector<vector<int>> &, int);
pair<int, int> greater_pair(pair<int, int>, pair<int, int>);

int main()
{
	int n;
	cin >> n;

	vector<vector<int>> tree = vector<vector<int>>(n + 1);
	for (int i = 0; i < n + 1; i++)
		tree[i] = vector<int>();

	for (int i = 0; i < (n - 1); i++)
	{
		int u, v;
		cin >> u >> v;
		tree[u].push_back(v);
	}

	path_info longes_path = longest_path(tree, 1);
	pair<int, int> greater_path = greater_pair(longes_path.v_path_in_root, longes_path.v_path_below);
	cout << greater_path.first + greater_path.second + 1;
}

pair<int, int> contribute(pair<int, int> main_pair, pair<int, int> contribution_pair)
{
	if (contribution_pair.first > main_pair.second)
	{
		if (contribution_pair.first > main_pair.first)
			return {contribution_pair.first, main_pair.first};
		else
			return {main_pair.first, contribution_pair.first};
	}
	else
		return main_pair;
}

path_info longest_path(const vector<vector<int>> &tree, int root)
{
	cout << root << ", ";

	path_info ret;
	for (int end_node : tree[root])
	{
		path_info cur = longest_path(tree, end_node);
		ret.v_path_below = greater_pair(ret.v_path_below, cur.v_path_below);
		ret.v_path_in_root = contribute(ret.v_path_in_root, cur.v_path_in_root);
	}

	cout << endl
		 << "a: " << root << ", ";

	ret.v_path_in_root.first++;
	ret.v_path_in_root.second++;

	ret.v_path_below = greater_pair(ret.v_path_below, ret.v_path_in_root);

	return ret;
}

pair<int, int> greater_pair(pair<int, int> pair1, pair<int, int> pair2)
{
	if (pair1.first + pair1.second > pair2.first + pair2.second)
		return pair1;
	else
		return pair2;
}