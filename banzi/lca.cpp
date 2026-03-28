#include<bits/stdc++.h>
#define N 601000
using namespace std;
vector<int> f[N];
int anc[N][20];
int dis[N], d[N];
int n, m, s;
void add(int u, int v)
{
	f[u].push_back(v);
	f[v].push_back(u);
}
void dfs(int u)
{
	for (int i = 0; i < f[u].size(); i++)
	{
		int v = f[u][i];
		if (v == anc[u][0])continue;
		d[v] = d[u] + 1;
		anc[v][0] = u;
		dfs(v);
	}
}
void init()
{
	for (int j = 1; j <= 18; j++)
	{
		for (int i = 1; i <= n; i++)
		{
			anc[i][j] = anc[anc[i][j - 1]][j - 1];
		}
	}
}
int lca(int u, int v)
{
	if (d[u] < d[v])swap(u, v);
	//cout << u << ' ' << v << endl;
	for (int i = 18; i >= 0; i--)
	{
		if (d[anc[u][i]] >= d[v])
		{
			u = anc[u][i];
			//cout << i << endl;
		}
	}
	//cout << u << ' ' << v << endl;
	if (u == v)return u;
	for (int i = 18; i >= 0; i--)
	{
		if (anc[u][i] != anc[v][i])
		{
			u = anc[u][i], v = anc[v][i];
		}
	}
	return anc[u][0];
}
signed main()
{
	return 0;
}