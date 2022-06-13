#include <bits/stdc++.h>
#include "../Cyctor.h"
using namespace std;

Cyctor perm[756756];
Cyctor ortho[111753];
Cyctor row[15];
bool found = false;
int c = 0;
int fact[12]; //contains the exact numbers of the factorials, instead of having to recompute them every time.
int n = 15, k = 3;

void findNextRow(int r)
{
    cout << endl;
    cout << "Finding row " << r+1 << ". Currently:" << endl;
    for (int i = 0; i < r; i++) cout << row[i] << '\n';
    cout << endl;
    if (r == 15)
    {
        found = true;
        return;
    }
    for (int i = 0; i < 111753; i++)
    {
        bool f_orthog = true;
        for (int j = 0; j < r; j++)
        {if (!row[j].orthog(ortho[i]))
            if (!row[j].orthog(ortho[i]))
            {
                f_orthog = false;
                break;
            }
        }
        if (f_orthog)
        {
            row[r] = ortho[i];
            findNextRow(r+1);
            if (found) return;
        }
    }
}

int main()
{
	spaceSetup(n,k);
	fact[0] = 1;
	for (int i = 1; i < 12; i++) fact[i] = fact[i-1]*i;
	for (int i = 0; i < 756756; i++) perm[i] = lexPerm(i);
	Cyctor id = perm[0];
	cout << 0 << " (id): " << id << endl;
    for (int i = 0; i < 756756; i++)
    {
        if (id.orthog(perm[i]))
        {
            ortho[c] = perm[i];
            c++;
        }
    }
    //cout << "c = " << c << endl;
    row[0] = Cyctor();
    row[1] = id;
    findNextRow(2);
}