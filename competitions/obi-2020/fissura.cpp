#include <bits/stdc++.h>
using namespace std;

char matrix[505][505];
bool visited_matrix[505][505];

bool is_possible(int i, int j, int n) {
	if (i < 0 || j < 0)
		return false;
	if (i >= n || j >= n)
		return false;
	return true;
}

int main() {
	int n, f;
	cin >> n >> f;
	char f_char = '0' + f;

	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++) {
			char height;
			cin >> height;
			matrix[i][j] = height;
		}

	queue<pair<int,int>> pos_queue = queue<pair<int,int>>();
	pos_queue.push(make_pair(0,0));
	while (!pos_queue.empty()) {
		pair<int,int> cur_pos = pos_queue.front();
		pos_queue.pop();
		visited_matrix[cur_pos.first][cur_pos.second] = true;

		char cur_height = matrix[cur_pos.first][cur_pos.second];
		if (cur_height <= f_char) {
			matrix[cur_pos.first][cur_pos.second] = '*';

			for (int add_i=-1; add_i<=1; add_i++)
				for (int add_j=-1; add_j<=1; add_j++) {
					int i = cur_pos.first + add_i;
					int j = cur_pos.second + add_j;
					if (is_possible(i,j,n) && !visited_matrix[i][j])
						pos_queue.push(make_pair(i,j));
				}
		}
	}

	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++)
			cout << matrix[i][j];
		cout << endl;
	}

	return 0;
}
