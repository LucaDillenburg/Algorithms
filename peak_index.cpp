#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {}

int peakIndex(int *nums, int size) //index of peak (i): nums[i-1] < nums[i] > nums[i+1]
{
	//a array necessarially has at least one peak. when after many divisions there's only a element left, that's one peak
	//ex: [1]=>i:0, [1,2]=>i:1

	int low = 0;
	int high = size - 1;
	while (low < high)
	{
		int mid = (high + low) / 2;
		if (nums[mid] > nums[mid + 1])
			//if the middle element is higher than the one in the right, the peak is the middle or one element in the left of the middle
			//(nums[mid-1]>nums[mid] => i:mid; else: nums[mid-2]>mid[mid-1] => return mid;... until mid=0)
			high = mid;
		else
			//for the same reason, if the middle element is shorter, the peak element is in the right of the middle
			low = mid + 1;
	}
	return low; //here: low==high => the elements was restricted to one (being certain that the peak is in the side chosen)
}