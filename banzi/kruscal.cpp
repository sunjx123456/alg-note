#include<bits/stdc++.h>
using namespace std;
#define N 1000000
#define M 4*N
long long n;
long long m;
#define INF 0x3f3f3f3f
int cnt, h[N], to[N], nxt[N], v[N];
int vis[N];
int dis[N];
struct edge
{
	int to, v, nxt;
	int u; int val;
}e[N];
void add(int x, int y, int z)
{
	e[++cnt].to = y;
	e[cnt].v = z;
	e[cnt].nxt = h[x];
	h[x] = cnt;
}
struct node
{
	int v; long long w;
};
int operator <(node a, node b)
{
	return a.w > b.w;
}
priority_queue<node> q;
int ans;
int tot;

int f[N];
int find(int x)
{
	if (x == f[x])return x;
	return f[x] = find(f[x]);
}
void merge(int x, int y)
{
	x = find(x), y = find(y);
	if (x != y)f[x] = y;

}
int cmp(edge a, edge b)
{
	return a.val < b.val;
}
void kruskal()
{
	sort(e + 1, e + m + 1, cmp);
	for (int i = 1; i <= m; i++)
	{
		int u = e[i].u, v = e[i].v;
		if (find(u) == find(v))continue;
		ans += e[i].val;
		merge(u, v);
		tot++;
	}
}