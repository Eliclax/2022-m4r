#include <bits/stdc++.h>
using namespace std;


// H_k(n). k is values, n is size
int k = 15, n = 15;
int grid[15][4], digitToAdd = 0, relIndex = 0, absIndex = 0, ii = 0, c = 0, jj = 0;
bool dupe = false;
long long int seed = 0;
long long int randa = 0, randb = 0;

long long int factorial(int nn)
{
    long long int fac = 1;
    for (int i = 1; i <= nn; i++)
    {
        fac*=i;
    }
    return fac;
}

bool duped(int g[][4], int cols)
{
    bool dupe_ = false;
    for (int i = 0; i < cols; i++)
    {
        for (int j = i+1; j < cols; j++)
        {
            for (int l = 0; l < n; l++)
            {
                for (int m = l+1; m < n; m++)
                {
                    if (((g[l][j] - g[l][i]) - (g[m][j] - g[m][i]))%k == 0)
                    {
                        cout << "Found zero with ijlm = " << i << " " << j << " " << l << " " << m << endl;
                        dupe_ = true;
                        break;
                    }
                }
                if (dupe_ == true) continue;
            }
            if (dupe_ == true) continue;
        }
        if (dupe_ == true) continue;
    }
    return dupe_;
}

int main()
{
    for (int i = 0; i < n; i++)
    {
        grid[i][0] = 0;
        grid[i][1] = i;
        grid[i][2] = -1;
        grid[i][3] = 0;
    }
    
    grid[0][2] = 0;
    
    bool found = false;
    int tryno = 0;
    long long int n_fac = factorial(n);
    long long int n_minus_one_fac = factorial(n-1);
    cout << "n_fac: " << n_fac << endl;
    
    while (!found)
    {
        randa = rand();
        randb = rand();
        seed = randa*(long(RAND_MAX)+1)+randb;
        //cout << "rand genereated: " << seed << endl;
        seed %= n_minus_one_fac;
        //cout << "seed: " << seed << endl;
        for (int i = 1; i < 15; i++) grid[i][2] = -1;
        //cout << "At this point: ";
        //for (int j = 0; j < n; j++) cout << grid[j][2] << " ";
        //cout << endl;
        for (int i = 13; i >= 0; i--)
        {
            digitToAdd = seed/factorial(i);
            seed %= factorial(i);
            relIndex = 1;
            absIndex = 1;
            while ((relIndex < digitToAdd + 1) || (grid[absIndex][2] != -1))
            {
                if (grid[absIndex][2] == -1) relIndex++;
                absIndex++;
            }
            grid[absIndex][2] = (grid[absIndex][1] + i + 1) % k;
            //for (int j = 0; j < n; j++) cout << grid[j][2] << " ";
            //cout << endl;
        }
        tryno++;
        cout << "Try number " << tryno << ": ";
        for (int i = 0; i < n; i++) cout << grid[i][2] << " ";
        cout << endl;
        if ((duped(grid,2)))
        {
            cout << "Above works" << endl;
            found = true;
        }
    }
    return 0;
}
