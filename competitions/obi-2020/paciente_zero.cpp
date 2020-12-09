#include <bits/stdc++.h>
using namespace std;

#define ll long long
int main() {
	int n, c;
	cin >> n >> c;

	vector<bool> arr_was_infected = vector<bool>(n+1, false);

	for (int index_a=0; index_a<c; index_a++) {
		int p, i;
		cin >> p >> i;
		for (int index_b=0; index_b<i; index_b++) {
			int xi;
			cin >> xi;
			arr_was_infected[xi] = true;
		}
	}

	for (int i=1; i<n+1; i++)
		if (arr_was_infected[i]==false)
			cout << i << endl;

	return 0;
}
