#include<bits/stdc++.h>
using namespace std;
#define N 100010
#define mod 998244353
int a[N];
int n;
int f[N][100];
int log_[N];
int gcd(int x, int y)
{
	if (y == 0)return x;
	else return gcd(y, x % y);
}
void init()
{
	for (int i = 2; i <= n; i++)
	{
		log_[i] = log_[i >> 1] + 1;
	}

	for (int i = 1; i <= n; i++)
	{
		f[i][0] = a[i];
	}
	for (int j = 1; (1 << j) <= n; j++)
	{
		for (int i = 1; i <= n - (1 << j) + 1; i++)
		{
			f[i][j] = gcd(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
		}
	}
}

int query(int l, int r)
{
	int k = log_[r - l + 1];
	return gcd(f[l][k], f[r - (1 << k) + 1][k]);
}

signed main()
{
	init();
	return 0;
}

