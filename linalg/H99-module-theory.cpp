#include <bits/stdc++.h>
#include "../Cyctor.h"
using namespace std;


int fid_[9] = {0,1,2,3,4,5,6,7,8};
int fx_[9] = {0,7,4,8,2,6,1,3,5};
Cyctor fid, fx;
Cyctor c;
int fact[12]; //contains the exact numbers of the factorials, instead of having to recompute them every time.
int n = 9, k = 9;
int box[9][9];

int main()
{
    spaceSetup(n,k);
    fid = Cyctor(9,9,fid_);
    fx = Cyctor(9,9,fx_);
    fact[0] = 1;
	for (int i = 1; i < 12; i++) fact[i] = fact[i-1]*i;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            box[i][j] = 0;
        }
    }
	for (int i = 0; i < fact[n]; i++)
    {
        c = lexPerm(i);
        box[(fid%c)++][(fx%c)++]++;
    }
    int total = 0;
    for (int i = 0; i < 9; i++)
    {
        int tote = 0;
        for (int j = 0; j < 9; j++)
        {
            cout << box[i][j] << " ";
            total += box[i][j];
            tote += box[i][j];
        }
        cout << tote << endl;
    }
    cout << endl;
    cout << total;
}