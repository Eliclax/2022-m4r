#include <bits/stdc++.h>
using namespace std;


// H_k(n). k is values, n is size
long long int k = 3, n = 6;
// grid has coords (RIGHT, DOWN)
long long int grid[6][6], digitToAdd = 0, relIndex = 0, absIndex = 0, ii = 0, c = 0, jj = 0;
long long int fact[16]; //contains the exact numbers of the factorials, instead of having to recompute them every time.
long long int seed = 0;
long long int randa = 0, randb = 0;
long long int maxRows = 0;
long long int gridstore[10000][6][6], storeCount = 0;
bool storeMatch, curGridMatch;

inline long long int modulo(long long int a, long long int b) {
  const long long int result = a % b;
  return result >= 0 ? result : result + b;
}

long long int factorial(long long int nn)
{
    long long int fac = 1;
    for (long long int i = 1; i <= nn; i++)
    {
        fac*=i;
    }
    return fac;
}

void print_grid(long long int rows)
{
    for (long long int i = 0; i < rows; i++)
    {
        for (long long int j = 0; j < n; j++)
        {
            cout << grid[j][i] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void store_grid()
{
    storeMatch = false;
    for (long long int i = 0; i < storeCount; i++)
    {
        curGridMatch = true;
        for (long long int j = 0; j < n; j++)
        {
            for (long long int m = 0; m < n; m++)
            {
                if (grid[j][m] != gridstore[i][j][m])
                {
                    curGridMatch = false;
                    break;
                }
            }
            if (curGridMatch == false) break;
        }
        if (curGridMatch == true) return;
    }
    if (storeMatch == false)
    {
        for (long long int i = 0; i < n; i++)
        {
            for (long long int j = 0; j < n; j++)
            {
                gridstore[storeCount][i][j] = grid[i][j];
            }
        }
        storeCount++;
        print_grid(n);
    }
}

bool isDuped(long long int g[][6], long long int rows)
{
    long long int diffs[k];
    for (long long int i = 0; i < rows; i++)
    {
        for (long long int j = i+1; j < rows; j++)
        {
            for (long long int l = 0; l < k; l++) diffs[l] = 0;
            for (long long int l = 0; l < n; l++)
            {
                diffs[modulo(g[l][i] - g[l][j], k)]++;
            }
            for (long long int l = 1; l < k; l++)
            {
                if (diffs[0] != diffs[l]) 
                {
                    //cout << "Discovered dupe at ijl = " << i << " " << j << " " << l << endl;
                    return true;
                }
            }
        }
    }
    return false;
}

void find_row(long long int curRow)
{
    grid[0][curRow] = 0;
    long long int value = 0, columnToAdd;
    for (long long int i = 0; i < fact[n-1]; i++)
    {
        value = i;
        for (long long int j = 0; j < n; j++)
        {
            for (long long int l = curRow; l < n; l++)
            {
                grid[j][l] = -1;
            }
        }
        grid[0][curRow] = 0;
        for (long long int j = n-2; j >= 0; j--)
        {
            columnToAdd = value/fact[j];
            value %= fact[j];
            relIndex = 1;
            absIndex = 1;
            while ((relIndex < columnToAdd + 1) || (grid[absIndex][curRow] != -1))
            {
                if (grid[absIndex][curRow] == -1) relIndex++;
                absIndex++;
            }
            grid[absIndex][curRow] = (j + 1) % k;
        }
        print_grid(curRow+1);
        if (!isDuped(grid, curRow + 1))
        {
            if (maxRows < curRow + 1) maxRows = curRow + 1;
            if (curRow + 1 < n)
            {
                find_row(curRow + 1);
            }
            else
            {
                store_grid();
            }
        }
    }
}

int main()
{
    for (long long int i = 0; i < 16; i++) fact[i] = factorial(i);
    for (long long int i = 0; i < n; i++)
    {
        grid[i][0] = 0;
        grid[i][1] = i%k;
        for (long long int j = 2; j < n; j++)
        {
            grid[i][j] = -1;
        }
    }
    
    find_row(2);
    
    cout << "Maximum rows found: " << maxRows << endl;
    cout << "Number of distinct matrices found: " << storeCount << endl;
    
    return 0;
    
    /*
    grid[0][2] = 0;
    
    long long int tryno = 0;
    long long int n_fac = factorial(n);
    long long int n_minus_one_fac = factorial(n-1);
    cout << "n_fac: " << n_fac << endl;
    
    for (long long int i = 500; i < 40320; i++)
    {
        ii = i;
        for (long long int j = 1; j < 9; j++) grid[j][2] = -1;
        for (long long int j = 7; j >= 0; j--)
        {
            digitToAdd = ii/factorial(j);
            ii %= factorial(j);
            relIndex = 1;
            absIndex = 1;
            while ((relIndex < digitToAdd + 1) || (grid[absIndex][2] != -1))
            {
                if (grid[absIndex][2] == -1) relIndex++;
                absIndex++;
            }
            grid[absIndex][2] = (grid[absIndex][1] + j + 1) % 9;
        }
        if (!isDuped(grid,3))
        {
            c++;
            for (long long int j = 0; j < 9; j++)
            {
                cout << grid[j][2] << " ";
            }
            cout << endl;
            
            
            
            
            for (long long int j = 0; j < factorial(8); j++)
            {
                jj = j;
                for (long long int l = 1; l < 9; l++) grid[l][3] = -1;
                for (long long int l = 7; l >= 0; l--)
                {
                    digitToAdd = jj/factorial(l);
                    jj %= factorial(l);
                    relIndex = 1;
                    absIndex = 1;
                    while ((relIndex < digitToAdd + 1) || (grid[absIndex][3] != -1))
                    {
                        if (grid[absIndex][3] == -1) relIndex++;
                        absIndex++;
                    }
                    grid[absIndex][3] = (grid[absIndex][2] + l + 1) % 9;
                }
                if (!isDuped(grid,4))
                {
                    for (long long int l = 0; l < 9; l++)
                    {
                        for (long long int m = 0; m < 4; m++)
                        {
                            cout << grid[l][m] << " ";
                        }
                        cout << endl;
                    }
                    cout << endl;
                }
            }
            
            
            
        }
    }
    cout << "Count: " << c;
    */
}
