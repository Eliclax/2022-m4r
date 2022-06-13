#include <bits/stdc++.h>
using namespace std;

inline int modulo(int a, int b);

void spaceSetup(int spaceLength_, int spaceModulus_);

class Cyctor
{
    public:
    int len;
    int modulus;
    int* e;

    Cyctor();

    Cyctor(int a);

    Cyctor(int n_, int k_);

	Cyctor(int n_, int k_, int a);

    Cyctor(int n_, int k_, int* e_);
	
	int& operator[](int i);

    void print();

    Cyctor add(Cyctor addend);

	Cyctor operator+(const Cyctor b);

    Cyctor add(int addend);

	Cyctor operator+(int b);

	friend Cyctor operator+(int a, Cyctor b);

	Cyctor neg();

	Cyctor operator-(Cyctor b);

	Cyctor operator-();

	int dot(Cyctor multiplicand);
    
	int operator*(const Cyctor b);

	Cyctor times(int scalar);

	Cyctor operator*(const int& b);

	friend Cyctor operator*(const int a, Cyctor b);

	friend ostream& operator<<(ostream& out, const Cyctor cyc);

	Cyctor odot(Cyctor multiplicand);

	Cyctor operator%(const Cyctor b);

	int sum();

	int operator++(int k);

	Cyctor pow(int k);

	Cyctor operator^(int k);

	bool orthog(Cyctor b);
};

long long binom(int n, int k);

Cyctor lexPerm(long long p, int n, int k);

Cyctor lexPerm(long long p);