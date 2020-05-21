#include <bits/stdc++.h>

using namespace std;

vector<int> merge_sort(vector<int>);

int main() {
	int length;
	cin >> length;

	vector<int> array = vector<int>(length);
	for (int i=0; i<length; i++)
		cin >> array[i];

	vector<int> sorted_array = merge_sort(array);
	for (int i=0; i<sorted_array.size(); i++)
		cout << sorted_array[i] << " ";
}

vector<int> new_array_of(vector<int> array, int begin, int last) {
	vector<int> ret = vector<int>(last - begin + 1);
	for (int i=begin; i<=last; i++) {
		ret[i-begin] = array[i];
	}
	return ret;
}

vector<int> merge_sort(vector<int> array) {
	if (array.size() <= 1)
		return array;

	int middle = array.size()/2;

	vector<int> left = new_array_of(array, 0, middle-1);
	vector<int> right = new_array_of(array, middle, array.size()-1);

	vector<int> sorted_left = merge_sort(left);
	vector<int> sorted_right = merge_sort(right);

	vector<int> sorted = vector<int>(array.size());
	int iSorted=0, i=0, j=0;
	while (i<sorted_left.size() && j<sorted_right.size()) {
		if (sorted_left[i] < sorted_right[j])
			sorted[iSorted++] = sorted_left[i++];
		else if (sorted_left[i] > sorted_right[j])
			sorted[iSorted++] = sorted_right[j++];
		else {
			sorted[iSorted++] = sorted_left[i++];
			sorted[iSorted++] = sorted_right[j++];
		}
	}

	while (i<sorted_left.size())
		sorted[iSorted++] = sorted_left[i++];
	while (j<sorted_right.size())
		sorted[iSorted++] = sorted_right[j++];

	return sorted;
}
