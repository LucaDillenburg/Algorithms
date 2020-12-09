#include <bits/stdc++.h>
using namespace std;

int dropsOfSeed();

int main(int argc, char **argv)
{
	int ret = dropsOfSeed();
	cout << ret;
}

int dropsOfSeed()
{
	int amntPositions, amntDrops;
	cin >> amntPositions >> amntDrops;

	int maxDays = 0;
	int lastDropPos = 0;

	for (int i = 0; i < amntDrops; i++)
	{
		int currPosition;
		cin >> currPosition;

		int days;
		if (i == 0)
			days = currPosition - 1;
		else
			days = ceil((currPosition - lastDropPos - 1) / 2.0f);

		if (days > maxDays)
			maxDays = days;

		lastDropPos = currPosition;

		if (i == amntDrops - 1)
		{
			int daysToRibbonEnd = amntPositions - lastDropPos;
			if (daysToRibbonEnd > maxDays)
				return daysToRibbonEnd;
			else
				return maxDays;
		}
	}
}