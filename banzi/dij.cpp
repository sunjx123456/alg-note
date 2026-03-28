#include<bits/stdc++.h>
using namespace std;
#define N 3000001
#define M 4*N
int n;
int m;
#define INF 0x7f7f7f7f
int cnt, h[N], to[N], nxt[N], v[N];
int vis[N];
void add(int x, int y, int z)
{
	to[++cnt] = y;
	nxt[cnt] = h[x];
	h[x] = cnt;
	v[cnt] = z;
}
int dis[N];
int ans;
int d[N];
struct node
{
	int v; int w;
}tmp;
int s, t;
int operator <(node a, node b)
{
	return a.w > b.w;
}
priority_queue<node> q;
void dijkstra()
{
	q.push({ s,0 });
	while (!q.empty())
	{
		int u = q.top().v;
		q.pop();
		if (vis[u])continue;
		vis[u] = 1;
		for (int i = h[u]; i; i = nxt[i])
		{
			int vv = to[i];
			if (dis[vv] > dis[u] + v[i])
			{
				dis[vv] = dis[u] + v[i];
				q.push({ vv,dis[vv] });
			}
		}
	}
}
signed main()
{
	return 0;
}