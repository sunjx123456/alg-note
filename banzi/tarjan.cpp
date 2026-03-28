#include <bits/stdc++.h>
using namespace std;
#define int long long
#define N 400010
#define M 2001
#define ec ' '
#define one 1ll
#define endl '\n'
const int mod = 998244353;
#define inf 0x7f7f7f7f
int n, m;
int dfn[N], low[N],stk[N];
int h[N], nxt[N], to[N]; bool cut[N];
int tot, cnt = 1; int bcnt, dcnt;
int top,root;
vector<int>dcc[N];
void add(int u, int v)
{
    to[++cnt] = v;
    nxt[cnt] = h[u];
    h[u] = cnt;
}
void tarjan(int x)
{
    dfn[x] = low[x] = ++tot;
    int flag = 0;
    if (x == root && h[x] == 0)
    {
        dcc[++dcnt] .push_back(x); return;
    }
    stk[++top] = x;
    for (int i = h[x]; i; i = nxt[i])
    {
        int v = to[i];
        if (!dfn[v])
        {
            tarjan(v);
            low[x] = min(low[x], low[v]);
            if (low[v] >= dfn[x])
            {
                flag++;
                if (x != root || flag > 1)
                {
                    cut[x] = 1;
                }
                dcc[++dcnt].push_back(x);
                do
                {
                    dcc[dcnt].push_back(stk[top]);
                } while (stk[top--] != v);
            }
        }
        else low[x] = min(low[x], dfn[v]);
    }
}