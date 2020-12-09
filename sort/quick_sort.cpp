#include <bits/stdc++.h>
using namespace std;

void quick_sort(int*, int, int);

int main() {
	int length;
	cin >> length;

	int *vector = (int*)malloc(sizeof(int)*length);
	for (int i=0; i<length; i++)
		cin >> vector[i];

	quick_sort(vector, 0, length-1);
	for (int i=0; i<length; i++)
		cout << vector[i] << " ";

	free(vector);
}

void swap(int *a, int *b) {
	int x = *a;
	*a = *b;
	*b = x;
}

void quick_sort(int *vector, int begin, int last) {
	cout << begin << " | " << last << endl;

	if (begin >= last)
		return;
	if (begin + 1 == last) {
		if (vector[begin] > vector[last])
	       		swap(&vector[begin], &vector[last]);
		return;
	}

	int pivot = vector[last];

	int next_smaller = begin;
	for (int i=begin; i<=last; i++) {
		if (vector[i] <= pivot)
			swap(&vector[i], &vector[next_smaller++]);
	}

	int index_pivot = next_smaller - 1;
	quick_sort(vector, begin, index_pivot - 1);
	quick_sort(vector, index_pivot + 1, last);
}

