#include<bits/stdc++.h>
using namespace std;

int perm[40320][9];
int part[40320];
int link[40320];
int fact[12]; //contains the exact numbers of the factorials, instead of having to recompute them every time.
int n = 9, k = 9;
int m = 40320; //if we compare all 8! it will take too long, so we're going to compare the first m of them
int iter = 3; //depth of search

inline int modulo(int a, int b) {
  const int result = a % b;
  return result >= 0 ? result : result + b;
}

void printr(int a) {
    for (int i = 0; i < 9 ; i++)
    {
        cout << perm[a][i] << " ";
    }
    cout << "| " << part[a] << " " << link[a] << endl;
}

bool compare(int a, int b)
{
    int diffs[9];
    for (int i = 0; i < n; i++) diffs[i] = 0;
    for (int i = 0; i < n; i++)
    {
        diffs[modulo(perm[a][i] - perm[b][i],9)]++;
    }
    for (int i = 1; i < n; i++)
    {
        if (diffs[i] != diffs[0]) return false;
    }
    return true;
}

void traceback(int a)
{
    printr(a);
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

int main()
{
    // initialise
    fact[0] = 1;
    for (int i = 1; i < 12; i++) fact[i] = fact[i-1]*i;
    for (int i = 0; i < fact[8]; i++)
    {
        for (int j = 0; j < 9; j++) perm[i][j] = -1;
        part[i] = 0;
        link[i] = -1;
    }
    
    
    // populate the perms
    for (int i = 0; i < fact[n-1]; i++)
    {
        int value = i;
        for (int j = n-2; j >= 0; j--)
        {
            int columnToAdd = value/fact[j];
            value %= fact[j];
            int relIndex = 1;
            int absIndex = 1;
            while ((relIndex < columnToAdd + 1) || (perm[i][absIndex] != -1))
            {
                if (perm[i][absIndex] == -1) relIndex++;
                absIndex++;
            }
            perm[i][absIndex] = (j + 1) % k;
        }
        perm[i][0] = 0;
    }
    
    
    // start the DFS to determine bipartivity
    part[40319] = 1;
    printr(40319);
    for (int d = 1; d <= iter; d++)
    {
        cout << "Starting on depth " << d << endl;
        for (int i = 0; i < m; i++)
        {
            if (d == 3)
            {
                if (i % 10 == 0)
                {
                    cout << "Reached i = " << i << endl;
                }
            }
            if (part[i] == d)
            {
                for (int j = 0; j < m; j++)
                {
                    if (i == j) continue;
                    if (compare(i,j))
                    {
                        //if ((part[j] != 0) && (part[j] % 2 != (d+1) % 2))
                        if ((part[j] == 4) && (part[i] == 4))
                        {
                            cout << "Failed while comparing i = " << i << " and j = " << j << endl;
                            traceback(i);
                            traceback(j);
                            return 0;
                        }
                        else if (part[j] == 0)
                        {
                            part[j] = d+1;
                            link[j] = i;
                            if (d == 1)
                            {
                                printr(j);
                            }
                        }
                    }
                }
            }
        }
    }
    
    ofstream depthlist;
    depthlist.open ("depthlist.txt", ios::out);
    
    for (int i = 0; i < 40320; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            depthlist << perm[i][j] << " ";
        }
        depthlist << "| " << part[i] << " " << link[i] << endl;
    }
    
    int assigned = 0;
    for (int i = 0; i < 40320; i++)
    {
        if (part[i] == 0)
        {
            cout << "perm " << i << " has not been assigned a part." << endl;
        }
        if (part[i] > 0)
        {
            assigned++;
        }
    }
    cout << assigned << " permutations have been assigned a part.";
}





















