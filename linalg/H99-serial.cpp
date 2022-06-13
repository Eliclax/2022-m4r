#include <bits/stdc++.h>
#include "../Cyctor.h"
using namespace std;

Cyctor perm[40320];
Cyctor ortho[225];
int fact[12]; //contains the exact numbers of the factorials, instead of having to recompute them every time.
int n = 9, k = 9;
int box[9];

int main()
{
	spaceSetup(n,k);
	fact[0] = 1;
	for (int i = 0; i < k; i++) box[i] = 0;
	for (int i = 1; i < 12; i++) fact[i] = fact[i-1]*i;
	for (int i = 0; i < fact[n-1]; i++) perm[i] = lexPerm(i);
	Cyctor id = perm[0];
	cout << 0 << ": " << id << endl;
	for (int i = 0; i < 9; i++)
	{
		cout << "(id^" << i << ")++ = " << id.pow(i)++ << endl;
	}
	/*
	Cyctor b = perm[290];
	int bi;
	while (!id.orthog(b))
	{
		bi = rand() % fact[n-1];
		b = perm[bi];
	}
	cout << bi << ": " << b << endl;
	*/
	int orthoCount = 0;
	for (int i = 0; i < fact[n-1]; i++)
	{
		if (perm[i].orthog(id))
		{
			ortho[orthoCount] = perm[i];
			orthoCount++;
			if (false) // Print info about cyctors
			{
				Cyctor p = perm[i];
				box[p * id]++;
				cout << p << " " << p * id << " ";
				cout << (p % id % (p - id))++ << " ";
				//cout << (p % id % (2*(p%p) - 3*(p%id) + 2*(id%id)))++ << " ";
				//cout << (2*(p%p) - 3*(p%id) + 2*(id%id))++ << endl;
				cout << (p%p%id)++ << " " << (p%id%id)++ << endl;
			}
		}
	}
	// for (int i = 0; i < k; i++) cout << i << " " << box[i] << endl;

	for (int i = 0; i < 225; i++)
	{
		for (int j = i; j < 225; j++)
		{
			if ((ortho[i] - ortho[j]).pow(2)++ == 6)
			{
				cout << ortho[i] << " - " << ortho[j] << "  =  " << ortho[i] - ortho[j] << ": ";
				for (int l = 1; l < 8; l++)
				{
					cout << " " << (ortho[i] - ortho[j]).pow(l)++;
				}
				cout << " | " << (ortho[i] % ortho[j] % (ortho[i] - ortho[j]))++;
				cout << endl;
			}
		}
	}
}