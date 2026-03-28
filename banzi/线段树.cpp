#include<bits/stdc++.h>
using namespace std;
#define N 115000
int n;
int m;
long long a[N]; long long w[4 * N];
long long lzy[N * 4];
void pushup(int u)
{
	w[u] = w[2 * u] + w[2 * u + 1];
}
void build(int u, int l, int r)
{
	if (l == r)
	{
		w[u] = a[l];
		return;
	}
	int mid = l + r >> 1;
	build(u * 2, l, mid); build(u * 2 + 1, mid + 1, r);
	pushup(u);
}
bool in(int L, int R, int l, int r)
{
	return(L >= l) && (R <= r);
}
bool out(int L, int R, int l, int r)
{
	return(L > r) || (R < l);
}
void maketag(int u, int len, long long x)
{
	lzy[u] += x;
	w[u] += x * len;
}
void pushdown(int u, int L, int R)
{
	int mid = L + R >> 1;
	maketag(u * 2, mid - L + 1, lzy[u]);
	maketag(u * 2 + 1, R - mid, lzy[u]);
	lzy[u] = 0;
}
long long query(int u, int L, int R, int l, int r)
{
	if (in(L, R, l, r))return w[u];
	else if (!out(L, R, l, r))
	{
		int mid = (R + L) >> 1;
		pushdown(u, L, R);
		return query(2 * u, L, mid, l, r) + query(2 * u + 1, mid + 1, R, l, r);
	}
	else return 0;
}
void update(int u, int L, int R, int l, int r, long long x)
{
	if (in(L, R, l, r))maketag(u, R - L + 1, x);
	else if (!out(L, R, l, r))
	{
		int mid = L + R >> 1;
		pushdown(u, L, R);
		update(u * 2, L, mid, l, r, x);
		update(u * 2 + 1, mid + 1, R, l, r, x);
		pushup(u);
	}
}
