#include <bits/stdc++.h>
#include "Cyctor.h"
using namespace std;

int spaceLength = 9, spaceModulus = 9;

void spaceSetup(int spaceLength_, int spaceModulus_)
{
	spaceLength = spaceLength_;
	spaceModulus = spaceModulus_;
}

inline int modulo(int a, int b) {
  const int result = a % b;
  return result >= 0 ? result : result + b;
}

Cyctor::Cyctor()
{
	len = spaceLength;
	modulus = spaceModulus;
	e = new int[len];
	for (int i = 0; i < len; i++) e[i] = 0;
}

Cyctor::Cyctor(int a)
{
	len = spaceLength;
	modulus = spaceModulus;
	e = new int[len];
	for (int i = 0; i < len; i++) e[i] = modulo(a, modulus);
}

Cyctor::Cyctor(int n_, int k_)
{
	len = n_;
	modulus = k_;
	e = new int[len];
	for (int i = 0; i < n_; i++) e[i] = 0;
}

Cyctor::Cyctor(int n_, int k_, int a)
{
	len = n_;
	modulus = k_;
	e = new int[len];
	for (int i = 0; i < len; i++) e[i] = modulo(a, modulus);
}

Cyctor::Cyctor(int n_, int k_, int* e_)
{
	len = n_;
	modulus = k_;
	e = new int[len];
	for (int i = 0; i < n_; i++)
	{
		e[i] = modulo(e_[i], modulus);
	}
}

int& Cyctor::operator[](int i) {return this->e[i];}

void Cyctor::print()
{
	for (int i = 0; i < this->len; i++)	cout << modulo(this->e[i], this->modulus) << ' ';
	cout << endl;
}

Cyctor Cyctor::add(Cyctor addend)
{
	if (this->len != addend.len) cout << "WARNING: addends' lengths do not match." << endl;
	try
	{
		if (this->modulus != addend.modulus) throw 0;
		Cyctor sum(this->len, this->modulus);
		for (int i = 0; i < this->len; i++)
		{
			sum.e[i] = modulo((this->e[i] + addend.e[i]), this->modulus);
		}
		return sum;
	}
	catch (int k)
	{
		cout << "ERROR: addends' spaces do not match. " << this->modulus << " vs " << addend.modulus << "." << endl;
		return *this;
	}
}

Cyctor Cyctor::operator+(const Cyctor b) {return this->add(b);}

Cyctor Cyctor::add(int addend)
{
	Cyctor sum(this->len, this->modulus);
	for (int i = 0; i < this->len; i++) sum.e[i] = modulo((this->e[i] + addend), this->modulus);
	return sum;
}

Cyctor Cyctor::operator+(int b) {return this->add(b);}

Cyctor operator+(int a, Cyctor b) {return b.add(a);}

Cyctor Cyctor::neg()
{
	Cyctor negative(this->len, this->modulus);
	for (int i = 0; i < this->len; i++) negative.e[i] = modulo(-this->e[i], modulus);
	return negative;
}

Cyctor Cyctor::operator-(Cyctor b) {return this->add(b.neg());}

Cyctor Cyctor::operator-() {return this->neg();}

int Cyctor::dot(Cyctor multiplicand)
{
	if (this->len != multiplicand.len) cout << "WARNING: factors' lengths do not match." << endl;
	try
	{
		if (this->modulus != multiplicand.modulus) throw 0;
		int sum = 0;
		for (int i = 0; i < this->len; i++)
		{
			sum += this->e[i] * multiplicand.e[i];
		}
		return modulo(sum, this->modulus);
	}
	catch (int k)
	{
		cout << "ERROR: factors' spaces do not match. " << this->modulus << " vs " << multiplicand.modulus << "." << endl;
		return 0;
	}
}

int Cyctor::operator*(const Cyctor b) {return this->dot(b);}

Cyctor Cyctor::times(int scalar)
{
	Cyctor result(this->len, this->modulus);
	for (int i = 0; i < this->len; i++) result.e[i] = modulo(this->e[i] * scalar, this->modulus);
	return result;
}

Cyctor Cyctor::operator*(const int& b) {return this->times(b);}

Cyctor operator*(const int a, Cyctor b) {return b.times(a);}

ostream& operator<<(ostream& out, const Cyctor cyc)
{
	out << "(";
	for (int i = 0; i < cyc.len - 1; i++) out << modulo(cyc.e[i], cyc.modulus) << " ";
	out << modulo(cyc.e[cyc.len-1], cyc.modulus) << ")";
	return out;
}

Cyctor Cyctor::odot(Cyctor multiplicand)
{
	if (this->len != multiplicand.len) cout << "WARNING: factors' lengths do not match." << endl;
	try
	{
		if (this->modulus != multiplicand.modulus) throw 0;
		Cyctor result(this->len, this->modulus);
		for (int i = 0; i < min(this->len, multiplicand.len); i++)
		{
			result.e[i] = modulo(this->e[i] * multiplicand.e[i], this->modulus);
		}
		return result;
	}
	catch (int k)
	{
		cout << "ERROR: factors' spaces do not match. " << this->modulus << " vs " << multiplicand.modulus << "." << endl;
		return Cyctor(this->len, this->modulus);
	}
}

Cyctor Cyctor::operator%(const Cyctor b) {return this->odot(b);}

int Cyctor::sum()
{
	int total = 0;
	for (int i = 0; i < this->len; i++)
	{
		total += this->e[i];
	}
	return modulo(total, this->modulus);
}

int Cyctor::operator++(int k) {return this->sum();}

bool Cyctor::orthog(Cyctor b)
{
	if (this->len != b.len) cout << "WARNING: lengths do not match." << endl;
	try
	{
		if (this->modulus != b.modulus) throw 0;
		int* diffs = new int[this->modulus];
		for (int i = 0; i < this->modulus; i++) diffs[i] = 0;
		for (int i = 0; i < this->len; i++)
		{
			diffs[modulo(this->e[i] - b.e[i], this->modulus)]++;
		}
		for (int i = 1; i < this->modulus; i++)
		{
			if (diffs[i] != diffs[0]) {delete diffs; return false;}
		}
		delete diffs;
		return true;
	}
	catch (int k)
	{
		cout << "ERROR: spaces do not match. " << this->modulus << " vs " << b.modulus << "." << endl;
		return false;
	}
}

Cyctor Cyctor::pow(int k)
{
	Cyctor power(this->len, this->modulus);
	for (int i = 0; i < this->len; i++) power[i] = 1;
	for (int i = 0; i < k; i++)
	{
		power = power % *this;
	}
	return power;
}

Cyctor Cyctor::operator^(int k) {return this->pow(k);}

long long binom(int n, int k)
{
	int* nn = new int[k];
	int* kk = new int[k];
	for (int i = 0; i < k ; i++)
	{
		nn[i] = n-i;
		kk[i] = i+1;
	}
	for (int i = 0; i < k; i++)
	{
		int j = 0;
		while (kk[i] != 1)
		{
			int d = __gcd(nn[j],kk[i]);
			nn[j] /= d;
			kk[i] /= d;
			j++;
		}
	}
	long long product = 1;
	for (int i = 0; i < k; i++) product *= nn[i];
	return product;
}

Cyctor lexPerm(long long p, int n, int k) // Generate the p-th lexicographical quasi-permutation of length n and modulus k
{
	Cyctor perm(n,k);
	int* rack = new int[k]; // An array counting how many of each digit is still to be inserted into perm
	for (int i = 0; i < k; i++) rack[i] = n/k + (i>=n%k ? 0 : 1); // Populate the rack
	long long poss = 1; // The number of possibilities left, given the current state of the rack & perm

	// Calculate poss
	int c = 0;
	for (int i = 0; i < k; i++)
	{
		c += rack[i];
		poss *= binom(c,rack[i]);
	}
	p = modulo(p, poss); // Normalise p
	
	// Genereate perm
	for (int i = 0; i < n; i++)
	{
		int d = 0;
		for (int j = 0; j < k; j++) d = __gcd(d,rack[j]);
		// cout << "The rack: ";
		// for (int j = 0; j < k; j++) cout << rack[j] << " ";
		// cout << endl;
		// cout << "poss right now is " << poss << endl;
		poss /= (n-i)/d; // the poss attributed to each "unit" of options. e.g. (1 1) (2 2), each unit assigned poss = 3
		// cout << "intermediate poss is " << poss << endl;
		// cout << "p is " << p << endl;
		int digit = p / poss;
		// cout << "digit is " << digit << endl;
		int selectSum = 0;
		for (int j = 0; j < k; j++)
		{
			if ((selectSum <= digit * d) && (selectSum + rack[j] > digit * d))
			{
				p -= (selectSum/d)*poss;
				poss *= rack[j]/d;
				rack[j]--;
				perm[i] = j;
				break;
			}
			selectSum += rack[j];
		}
		// for (int j = 0; j < i+1; j++)
		// {
		// 	cout << perm[j] << " ";
		// }	
		// cout << endl << endl;
		// p = modulo(p, poss);
	}
	return perm;
}

Cyctor lexPerm(long long p) // Generate the p-th lexicographical quasi-permutation
{
	return lexPerm(p, spaceLength, spaceModulus);
}