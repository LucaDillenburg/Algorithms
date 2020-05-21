#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv)
{
	//get input
	int s;
	cin >> s;

	int skillsQuadronians[s];
	for (int i = 0; i < s; i++)
		cin >> skillsQuadronians[i];

	int skillsNlogonians[s];
	for (int i = 0; i < s; i++)
		cin >> skillsNlogonians[i];

	//resuolution
	sort(skillsQuadronians, skillsQuadronians + s); //O(n log n)
	sort(skillsNlogonians, skillsNlogonians + s);	//O(n log n)

	int amntBattlesWin = 0;
	int iNlogonians = s - 1, iQuadronians = s - 1; //indexes
	while (iQuadronians >= 0)					   //O(n)
	{
		if (skillsNlogonians[iNlogonians] > skillsQuadronians[iQuadronians])
		{
			amntBattlesWin++;
			iNlogonians--;
		}
		iQuadronians--;
	}
	cout << amntBattlesWin;
}