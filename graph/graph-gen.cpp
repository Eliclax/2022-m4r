#include <bits/stdc++.h>
#define nnn 3
#define kkk 3
#define nnnm1fac 2 //exactly (n-1)!
using namespace std;


// H_k(n). k is values, n is size
long long int k = kkk, n = nnn, n_1fac = nnnm1fac;
long long int fact[16]; //contains the exact numbers of the factorials
long long int cyct[nnnm1fac][nnn];
int graph[nnnm1fac][nnnm1fac];

class Cyctor {
    public:
        int myNum;
        string myString;
};

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

bool orthog(int a, int b)
{
    long long int bucket[nnn];
    for (long long int i = 0; i < n; i++) bucket[i] = 0;
    for (long long int i = 0; i < n; i++)
    {
        bucket[modulo(cyct[a][i] - cyct[b][i],n)]++;
    }
    for (long long int i = 1; i < n; i++)
    {
        if (bucket[0] != bucket[i]) return false;
    }
    return true;
}

int main()
{
    for (long long int i = 0; i < 16; i++) fact[i] = factorial(i);
    for (long long int i = 0; i < fact[n-1]; i++) for (long long int j = 0; j < fact[n-1]; j++) graph[i][j] = 0;
    for (long long int i = 0; i < fact[n-1]; i++)
    {
        for (long long int j = 1; j < n; j++) cyct[i][j] = -1;
        cyct[i][0] = 0;
        long long int value = i, columnToAdd;
        for (long long int j = n-2; j >= 0; j--)
        {
            columnToAdd = value/fact[j];
            value %= fact[j];
            long long int relIndex = 1;
            long long int absIndex = 1;
            while ((relIndex < columnToAdd + 1) || (cyct[i][absIndex] != -1))
            {
                if (cyct[i][absIndex] == -1) relIndex++;
                absIndex++;
            }
            cyct[i][absIndex] = (j + 1) % k;
        }
    }
    for (long long int i = 0; i < fact[n-1]; i++)
    {
        for (long long int j = i+1; j < fact[n-1]; j++)
        {
            if (orthog(i,j))
            {
                graph[i][j] = 1;
                graph[j][i] = 1;
            }
        }
    }
    for (long long int i = 0; i < fact[n-1]; i++)
    {
        for (long long int j = 0; j < fact[n-1]; j++)
        {
            if (graph[i][j] == 0) cout << "  ";
            else cout << "● ";
        }
        cout << endl;
    }
}
