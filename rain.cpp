#include <bits/stdc++.h>
using namespace std;

// https://olimpiada.ic.unicamp.br/pratique/p2/2016/f1/chuva/
int main(int argc, char **argv)
{
	int amntSessions;
	cin >> amntSessions;

	//precisa ter uma barreira na esquerda e na esquerda
	int amntSessionsWithWater = 0;

	struct Partition
	{
		int height, amntSessions;
	} partitions[amntSessions] /*max length*/;
	int iLast = -1;

	for (int i = 0; i < amntSessions; i++) //O(n)
	{
		int heightCurrSession;
		cin >> heightCurrSession;

		bool createPartition = false;
		if (i == 0) //first session
			createPartition = true;
		else
		{
			//the current session can be
			//1. in a level below                      => new partition
			//1. in the same level as the last one     => increment number of sessions in the
			//2. higher than the last one              => see there

			const int heightLastHighPartition = partitions[iLast].height;

			if (heightCurrSession == heightLastHighPartition) // same level
				partitions[iLast].amntSessions++;
			else if (heightCurrSession > heightLastHighPartition) // level up
			{
				//back n partitions (and add the sessions as with water)
				do
				{
					//if there is a left barrier to this partition
					if (iLast > 0 /*so that there is something before the last*/ &&
						partitions[iLast - 1].height > partitions[iLast].height)
						amntSessionsWithWater += partitions[iLast].amntSessions;
					iLast--;
				} while (iLast >= 0 && heightCurrSession > partitions[iLast].height);

				//if the there is any partition left, see if the current partition is in the same partition than the last or if it will be necessary to create another partition
				if (iLast >= 0)
				{
					if (heightCurrSession == partitions[iLast].height)
						partitions[iLast].amntSessions++;
					else
						createPartition = true;
				}
				else
					createPartition = true;
			}
			else /*if (heightCurrSession < heightLastHighPartition)*/ // level down
				createPartition = true;
		}

		if (createPartition)
		{
			iLast++;
			partitions[iLast].height = heightCurrSession;
			partitions[iLast].amntSessions = 1;
		}
	}

	cout << amntSessionsWithWater;
}