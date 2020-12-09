#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {}

vector<vector<int>> threeSum(vector<int> &nums)
{
	//Solution: O(N^2). using sort

	std::sort(nums.begin(), nums.end()); //sort
	vector<vector<int>> res;

	const int length = nums.size(); //length
	for (int i = 0; i < length; i++)
	{
		const int sumTarget = -nums[i]; //-a = b+c

		//if the target sum is less than zero, it means that you are already on the positive side of the sequence (and in this side you cannot have 3 values that summed up, results in zero)
		if (sumTarget < 0)
			break;

		int front = i + 1;
		int back = length - 1;

		//find all pairs that summed up results in sumTarget (set the pointer to the begin and end and moving it depending on the values)
		while (front < back)
		{
			const int sum = nums[front] + nums[back];

			if (sum > sumTarget) //it means the back is too to the right
				back--;
			else if (sum < sumTarget) //it means the front is too to the left
				front++;
			else //the sum is equal to the target
			{
				vector<int> triplet{-sumTarget, nums[front], nums[back]};
				res.push_back(triplet);

				// Processing duplicates of Number 2: Rolling the front pointer to the next different number forwards
				while (front < back && nums[front] == triplet[1])
					front++;

				// Processing duplicates of Number 3: Rolling the back pointer to the next different number backwards
				while (front < back && nums[back] == triplet[2])
					back--;
			}
		}

		// Processing duplicates of Number 1
		while (i + 1 < length && nums[i + 1] == nums[i])
			i++;
	}

	return res;
}