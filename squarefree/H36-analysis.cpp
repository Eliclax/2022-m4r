#include <bits/stdc++.h>
#include "../Cyctor.h"
using namespace std;

Cyctor perm[90];
Cyctor ortho[27];
Cyctor row[6];
bool found = false;
int c = 0;
int fact[12]; //contains the exact numbers of the factorials, instead of having to recompute them every time.
int n = 6, k = 3;
int box[9];

void findNextRow(int r)
{
    cout << endl;
    cout << "Finding row " << r << endl;
    for (int i = 0; i < r; i++) cout << row[i] << '\n';
    cout << endl;
    if (r == 6)
    {
        found = true;
        return;
    }
    for (int i = 0; i < 27; i++)
    {
        bool f_orthog = true;
        for (int j = 0; j < r; j++)
        {
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
	for (int i = 0; i < 90; i++) perm[i] = lexPerm(i);
	Cyctor id = perm[0];
	cout << 0 << ": " << id << endl;
    for (int i = 0; i < 90; i++)
    {
        // cout << perm[i] << endl;
        if (id.orthog(perm[i]))
        {
            ortho[c] = perm[i];
            c++;
        }
    }
    row[0] = Cyctor();
    row[1] = id;
    findNextRow(2);
}