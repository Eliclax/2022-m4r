#include <bits/stdc++.h>
#include "../Cyctor.h"
using namespace std;

int fid_[9] = {0,1,2,3,4,5,6,7,8};
Cyctor fid;
Cyctor row[3];
bool found = false;
int c = 0;
int fact[12]; //contains the exact numbers of the factorials, instead of having to recompute them every time.
int n = 9, k = 9;
int box[9] = {};

int main()
{
	spaceSetup(n,k);
    fid = Cyctor(9,9,fid_);
	fact[0] = 1;
	for (int i = 1; i < 12; i++) fact[i] = fact[i-1]*i;

    for (int i = 0; i < fact[8]; i++)
    {
        row[0] = lexPerm(i);
        //cout << row[0] << endl;
        if (row[0][3] != 1) continue;
        if (row[0][6] != 2) continue;
        //cout << row[0] << endl;
        row[1] = row[0] - fid;
        row[2] = row[1] - fid;

        bool eq3 = true;
        for (int j = 0; j < 9; j++)
        {
            box[j] = 0;
        }

        for (int a = 0; a < 3; a++)
        {
            for (int b = 0; b < 9; b++)
            {
                box[row[a][b]]++;
            }
        }
        for (int j = 0; j < 9; j++)
        {
            //cout << box[j] << " ";
            if (box[j] != 3)
            {
                eq3 = false;
            }
        }
        if (eq3)
        {
            cout << "eq3 is " << eq3 << endl;
            cout << row[0] << endl << row[1] << endl << row[2] << endl << endl;
        }
    }
}