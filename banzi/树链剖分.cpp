#include<bits/stdc++.h>
#define N 500001
#define int long long
using namespace std;
int n, m;
int r, mod;
int a[N], w[N], d[N], dfn[N], rdfn[N], wc[N], siz[N],top[N],fat[N];
int cnt;
int lzy[N];
vector<int>f[N];
void dfs1(int u,int fa)
{
	fat[u] = fa;
	d[u] = d[fa] + 1;
	siz[u] = 1;
	for (int i = 0; i < f[u].size(); i++)
	{
		int v = f[u][i];
		if (v != fa)
		{
			dfs1(v, u);
			siz[u] += siz[v];
			if (siz[v] > siz[wc[u]])
			{
				wc[u] = v;
			}
		}
	}
}
void dfs2(int u,int t)
{
	dfn[u] = ++cnt;
	rdfn[cnt] = u;
	top[u] = t;
	if (wc[u])
	{
		dfs2(wc[u],t);
		for (int i = 0; i < f[u].size(); i++)
		{
			int v = f[u][i];
			if (v != fat[u]&&v!=wc[u])
			{
				dfs2(v, v);
			}
		}
	}
}
void pushup(int u)
{
	w[u] = (w[u * 2] + w[u * 2 + 1])%mod;
}
void build(int u, int l, int r)
{
	if (l == r)
	{
		w[u] = a[rdfn[l]]; return;
	}
	int mid = l + r >> 1;
	build(u * 2, l, mid);
	build(u * 2 + 1, mid + 1, r);
	pushup(u);
}
bool in(int L, int R, int l, int r)
{
	return (L >= l) && (R <= r);
}
bool out(int L, int R, int l, int r)
{
	return (L > r) || (R < l);
}
void maketag(int u, int len, int x)
{
	w[u] = (w[u] + len * x) % mod;
	lzy[u] = (lzy[u] + x) % mod;

}
void pushdown(int u, int l, int r)
{
	int mid = l + r >> 1;
	maketag(u * 2, mid - l + 1, lzy[u]);
	maketag(u * 2 + 1, r - mid, lzy[u]);
	lzy[u] = 0;
}
int query(int u, int L, int R, int l, int r)
{
	if (in(L, R, l, r))return w[u]%mod;
	else if (!out(L, R, l, r))
	{
		int mid = L + R >> 1;
		pushdown(u, L, R);
		return (query(u * 2, L, mid, l, r) + query(u * 2 + 1, mid + 1, R, l, r) )% mod;
	}
	else return 0;
}
void update(int u, int L, int R, int l,int r,int x)
{
	if (in(L, R, l, r))maketag(u, R - L + 1, x);
	else if (!out(L, R, l, r))
	{
		int mid = L + R >> 1;
		pushdown(u, L, R);
		update(u*2, L, mid, l, r, x);
		update(u * 2 + 1, mid + 1, R, l, r, x);
		pushup(u);
	}
}
void upd(int x, int y, int z)
{
	while (top[x] != top[y])
	{
		if (d[top[x]] < d[top[y]])
		{
			swap(x, y);
		}
		update(1, 1, n, dfn[top[x]], dfn[x], z);
		x = fat[top[x]];
	}
	update(1, 1, n, min(dfn[x], dfn[y]), max(dfn[x], dfn[y]), z);
}
int qur(int x, int y)
{
	int ans = 0;
	while (top[x] != top[y])
	{
		if (d[top[x]] < d[top[y]])swap(x, y);
		ans += query(1, 1, n, dfn[top[x]], dfn[x]);
		ans %= mod;
		x = fat[top[x]];
	}
	return (ans + query(1, 1, n, min(dfn[x], dfn[y]), max(dfn[x], dfn[y]))) % mod;
}