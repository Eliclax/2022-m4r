#include <bits/stdc++.h>
using namespace std;

// H_k(n). k is values, n is size
// grid has coords (RIGHT, DOWN)
long long invariant[26][26], grid[25][25];
long long spf = 0;
long long total = 0, product = 1;

long long smallest_pfactor(long long n)
{
    for (long long i = 2; i <= n; i++)
    {
        if (n % i == 0) return i;
    }
    return n;
}

int main()
{
    for (long long i = 0; i < 26; i++)
    {
        for (long long j = 0; j < 26; j++)
        {
            invariant[i][j] = 0;
        }
    }
    for (long long kn = 2; kn <= 25; kn++)
    {
        spf = smallest_pfactor(kn);
        for (long long rows = 2; rows <= spf; rows++)
        {
            
            //initialising the grid
            for (long long i = 0; i < kn; i++)
            {
                for (long long j = 0; j < rows; j++)
                {
                    grid[i][j] = (i*j)%kn;
                }
            }
            
            //calculating the invariant
            total = 0;
            for (long long i = 0; i < kn; i++)
            {
                for (long long j = 0; j < rows; j++)
                {
                    product = 1;
                    for (long long k = 1; k < rows; k++)
                    {
                        product *= (((grid[i][(j+k)%rows] - grid[i][j])%kn)+kn)%kn;
                    }
                    total += product;
                }
            }
            invariant[kn][rows] = total;
        }
    }
    
    
    //print the invariant array
    for (long long i = 0; i < 26; i++)
    {
        for (long long j = 0; j < 26; j++)
        {
            cout << invariant[j][i] << ' ';
        }
        cout << endl;
    }
}
