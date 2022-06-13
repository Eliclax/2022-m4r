#include <bits/stdc++.h>
#include "../Cyctor.h"
using namespace std;

Cyctor perm[5040];
Cyctor ortho[28];
bool checked[28] = {false};
int eclass[28] = {0};
int eclassno = 0;
bool found = false;
int c = 0;
int fact[12]; //contains the exact numbers of the factorials, instead of having to recompute them every time.
int n = 7, k = 7;
int hi[9] = {0,1,2,3,4,5,6};
int hi2[9] = {0,2,4,6,1,3,5};

int diff(Cyctor a, Cyctor b)
{
    Cyctor e = a - b;
    int d = 0;
    for (int i = 0; i < e.len; i++)
    {
        if (e[i] != 0) d++;
    }
    return d;
}

int checkUpTo()
{
    for (int i = 0; i < 28; i++)
    {
        if (checked[i] == false) return i;
    }
    return 28;
}

int main()
{
	spaceSetup(n,k);
	fact[0] = 1;
	for (int i = 1; i < 12; i++) fact[i] = fact[i-1]*i;
	for (int i = 0; i < 5040; i++) perm[i] = lexPerm(i);
	Cyctor id = perm[0];
	cout << " (id): " << id << endl;
	Cyctor id2 = Cyctor(n,k,hi2);
	cout << " (id2): " << id2 << endl;

    ofstream myfile;
    myfile.open ("H77-4row-4perms.txt");

    for (int i = 0; i < 5040; i++)
    {
        if (id.orthog(perm[i]) && id2.orthog(perm[i]))
        {
            myfile << perm[i] << endl;
            ortho[c] = perm[i];
            c++;
        }
    }
    cout << "Number of orthog: " << c << endl;
    myfile.close();

    if (true)
    {
        while(checkUpTo() < 28)
        {
            eclassno++;
            queue<int> q = {};
            int cut = checkUpTo();
            q.push(cut);
            checked[cut] = true;
            eclass[cut] = eclassno;
            c = 0;

            while(!q.empty())
            {
                c++;
                int cur = q.front();
                q.pop();
                eclass[cur] = eclassno;
                if (c < 3) cout << c << " " << ortho[cur] << endl;
                for (int i = 0; i < 28; i++)
                {
                    if (checked[i] == false && diff(ortho[i], ortho[cur]) == 4)
                    {
                        q.push(i);
                        checked[i] = true;
                    }
                }
            }
            cout << "c = " << c << endl;
        }

        myfile.open ("H77-4row-4perm-classes.txt");
        for (int i = 0; i < 28; i++)
        {
            myfile << ortho[i] << " " << eclass[i] << endl;
        }
        myfile.close();
    }
}
