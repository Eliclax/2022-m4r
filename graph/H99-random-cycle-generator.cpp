#include <bits/stdc++.h>
using namespace std;

int perm[40320][9];
int part[40320];
int link[40320];
int path[40321];
int fact[12]; //contains the exact numbers of the factorials, instead of having to recompute them every time.
int n = 9, k = 9;
int m = 40320; //if we orthog all 8! it will take too long, so we're going to orthog the first m of them
int gen_no = 20; //number of cycles to generate

inline int modulo(int a, int b) {
  const int result = a % b;
  return result >= 0 ? result : result + b;
}

// print a perm
void printr(int a, ostream& streamout) {
    for (int i = 0; i < 9 ; i++)
    {
        streamout << perm[a][i] << " ";
    }
    streamout << endl;
}

bool orthog(int a, int b)
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
    printr(a, cout);
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
            do
            {
                path[hodos] = rand()%fact[n-1];
            }
            while (!orthog(path[hodos-1],path[hodos]) || (hodos > 1 && path[hodos-2] == path[hodos]));
            hodos++;
            if (hodos > 20) goto hi;
        }
        
        // print path
        paths << "Length: " << hodos - findCycle(hodos) - 1 << "     which is " << (hodos - findCycle(hodos) - 1)%3 << " (mod 3)" << endl;
        for (int j = 0; j < hodos; j++)
        {
            if (j == hodos - findCycle(hodos)) paths << "========================" << endl;
            printr(path[j], paths);
        }
        paths << "Length: " << hodos - findCycle(hodos) - 1 << "     which is " << (hodos - findCycle(hodos) - 1)%3 << " (mod 3)" << endl;
        paths << "========================================" << endl;
        
    }
}





















