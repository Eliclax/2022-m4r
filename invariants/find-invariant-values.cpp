#include <bits/stdc++.h>
using namespace std;

long long int grid[9], value = 0;
long long int fact[10], columnToAdd = 0, absIndex = 0, relIndex = 0;
long long int track[9];



long long int one_sum()
{
	int total = 0;
	for (int i = 0; i < 9; i++)
	{
		total += i*grid[i];
	}
	return total;
}

int main()
{
	fact[0] = 1;
	for (int i = 1; i <= 9; i++) fact[i] = fact[i-1]*i;
	grid[0] = 0;
	for (int i = 0; i < 9; i++)
	{
		track[i] = 0;
	}
	for (int i = 0; i < fact[8]; i++)
	{
		for (int j = 1; j < 9; j++)
		{
			grid[j] = -1;
		}
		value = i;
		for (int j = 7; j >= 0; j--)
		{
			columnToAdd = value/fact[j];
            value %= fact[j];
            relIndex = 1;
            absIndex = 1;
            while ((relIndex < columnToAdd + 1) || (grid[absIndex] != -1))
            {
                if (grid[absIndex] == -1) relIndex++;
                absIndex++;
            }
            grid[absIndex] = (j + 1) % 9;
		}
		track[one_sum()%9]++;
		if (one_sum() % 9 == 6)
		{
			for (int i = 0; i < 9; i++)
			{
				cout << grid[i];
			}
			cout << endl;
		}
	}
	cout << endl;
	for (int i = 0; i < 9; i++)
	{
		cout << track[i] << endl;
	}
	cout << endl;
}







