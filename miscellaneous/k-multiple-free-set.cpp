#include <bits/stdc++.h>
using namespace std;

#define ll long long

// site: https://codeforces.com/contest/275/problem/C
int main() {
	ll n, k;
	cin >> n >> k;

	vector<ll> vector_values = vector<ll>(n);
	vector<bool> vector_removed = vector<bool>(n);
	for (ll i=0; i<n; i++) {
		cin >> vector_values[i];
		vector_removed[i] = false;
	}

	sort(vector_values.begin(), vector_values.end()); //O(n log n)
	
	ll length_free_set = 0;

	// O(n log n)
	for (ll i=0; i<n; i++) { //O(n)
		if (vector_removed[i])
			continue;
		length_free_set++;

		ll i_search = lower_bound(vector_values.begin(), vector_values.end(), vector_values[i]*k) - vector_values.begin(); //O(log n)
		if (vector_values[i_search] == k*vector_values[i])
			vector_removed[i_search] = true;
	}

	cout << length_free_set << endl;
}
