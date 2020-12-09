#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv)
{
	string in;
	cin >> in;
	cout << myAtoi(in);
}

int myAtoi(string str)
{
	const int imin = numeric_limits<int>::min();
	const int imax = numeric_limits<int>::max();

	long int ret = 0;
	bool numericStarted = false;
	bool positive = true;
	for (char &c : str)
	{
		if (c >= '0' && c <= '9')
		{
			numericStarted = true;

			int n;
			switch (c)
			{
			case '0':
				n = 0;
				break;
			case '1':
				n = 1;
				break;
			case '2':
				n = 2;
				break;
			case '3':
				n = 3;
				break;
			case '4':
				n = 4;
				break;
			case '5':
				n = 5;
				break;
			case '6':
				n = 6;
				break;
			case '7':
				n = 7;
				break;
			case '8':
				n = 8;
				break;
			case '9':
				n = 9;
				break;
			}

			if (positive)
				ret = ret * 10 + n;
			else
				ret = ret * 10 - n;

			if (ret < imin)
				return imin;
			if (ret > imax)
				return imax;
		}
		else if (c == '+' || c == '-')
		{
			if (numericStarted)
				break; //ignore the characters after the numeric value

			numericStarted = true; //its not acceptable for a character different from a number come next
			if (c == '-')
				positive = false;
		}
		else
		{
			if (c != ' ' || numericStarted)
				break;
		}
	}

	return ret;
}
