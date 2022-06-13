#include <bits/stdc++.h>
#include "../Cyctor.h"
using namespace std;

Cyctor perm[40320];
int permu[9];
int part[40320];
int link[40320];
int path[40321];
int fact[12]; //contains the exact numbers of the factorials, instead of having to recompute them every time.
int n = 9, k = 9;
int m = 40320; //if we orthog all 8! it will take too long, so we're going to orthog the first m of them
int gen_no = 5000; //number of cycles to generate
int freq[40320];
int mod3[3];

void traceback(int a)
{
    cout << perm[a] << endl;
    if (link[a] == -1)
    {
        cout << "Traceback ended ================" << endl;
        return;
    }
    else
    {
        traceback(link[a]);
    }
}

int findCycle(int hodos)
{
    for (int i = 0; i < hodos-1; i++)
    {
        if (path[i] == path[hodos-1]) return i;
    }
    return -1;
}

int main()
{
    // initialise
    spaceSetup(n, k);
    fact[0] = 1;
    for (int i = 1; i < 12; i++) fact[i] = fact[i-1]*i;
    Cyctor* perm = new Cyctor[fact[n-1]];
    for (int i = 0; i < fact[n-1]; i++)
    {
        mod3[i%3] = 0;
        freq[i] = 0;
        part[i] = 0;
        link[i] = -1;
    }
    
    // populate the perms
    for (int i = 0; i < fact[n-1]; i++)
    {
        perm[i] = lexPerm(i);
    }
    
    ofstream paths;
    paths.open ("paths.txt", ios::out);
    
    
    // start searching for random cycles
    for (int i = 0; i < gen_no; i++)
    {
        hi:
        path[0] = 0;
        int hodos = 1;
        while (findCycle(hodos) == -1)
        {
            // cout << perm[path[hodos]] << endl;
            do
            {
                path[hodos] = rand()%fact[n-1];
            }
            while (!perm[path[hodos-1]].orthog(perm[path[hodos]]) || (hodos > 1 && path[hodos-2] == path[hodos]));
            hodos++;
            // if (hodos > 20) goto hi;
        }
        
        // print path
        int f = findCycle(hodos);
        // cout << "Length: " << hodos - f - 1 << "     which is " << (hodos - f - 1)%3 << " (mod 3)" << endl;
        if (i % 500 == 0) cout << "up to " << i << endl;
        freq[hodos - f - 1]++;
        mod3[(hodos - f - 1)%3]++;
        // paths << "Length: " << hodos - f - 1 << "     which is " << (hodos - f - 1)%3 << " (mod 3)" << endl;
        // for (int j = 0; j < hodos; j++)
        // {
        //     if (j == f) paths << "========================" << endl;
        //     paths << perm[path[j]] << endl;
        // }
        // paths << "Length: " << hodos - f - 1 << "     which is " << (hodos - f - 1)%3 << " (mod 3)" << endl;
        // paths << "========================================" << endl;
    }
    for (int i = 0; i < 500; i++)
    {
        cout << i << ": ";
        if (freq[i] == 0) cout << endl;
        else cout << freq[i] << endl;
    }
    for (int i = 0; i < 3; i++)
    {
        cout << "mod 3 " << i << ": " << mod3[i] << endl;
    }
}





















