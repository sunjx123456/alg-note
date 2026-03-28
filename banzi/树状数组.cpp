#include<bits/stdc++.h>
using namespace std;
#define N 515000
int n, m;
int c[N];
int lowbit(int x)
{
	return x & (-x);
}
int sum(int x)
{
	int res = 0;
	for (int i = x; i; i -= lowbit(i)) res += c[i];
	return res;
}
void add(int x, int y)
{
	for (int i = x; i <= n; i += lowbit(i))
	{
		c[i] += y;
	}
}