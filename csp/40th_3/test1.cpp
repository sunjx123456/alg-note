#include <bits/stdc++.h>
using namespace std;
#define int long long
#define N 300100
#define M 510
const int inf = 1e18,mod=1e9+7;
#define ec ' '
char a[M][M];
int stk[N];
int n, m;
char b[M][M];
int z;
//#define endl '\n'可以看出不一定endl就慢
vector<char>ans;
void rev(int u, int v,int x,int y, int cnt)
{
	if (cnt == 0)return;
	for (int i = u; i <= x; i++)
	{
		for (int j = v; j <= y; j++)
		{
			b[i][j] = a[i][j];
		}
	}//有用的就复制，没用的别复制，csp的数据松有可能就差在这点小常数
	int row = x + u , col = y + v ;
	int p = u + x + v + y, q = v + y - u - x;
	p /= 2, q /= 2;
	if (cnt == 1)
	{
		for (int i = u; i <= x; i++)
		{
			for (int j = v; j <= y; j++)
			{
				a[j-q][p  - i] = b[i][j];
			}
		}
	}
	else if (cnt == 2)
	{
		for (int i = u; i <= x; i++)
		{
			for (int j = v; j <= y; j++)
			{
				a[row - i][col - j] = b[i][j];
			}
		}
	}
	else
	{
		for (int i = u; i <= x; i++)
		{
			for (int j = v; j <= y; j++)
			{
				a[p - j][i+q] = b[i][j];
			}
		}
	}
}
void change(int u, int v, int x, int y, int op)
{
	if (op == -1)
	{
		for (int i = u; i <= x; i++)
		{
			for (int j = v; j <= (v + y) / 2; j++)
			{
				swap(a[i][j], a[i][v + y- j]);
			}
		}
	}
	else
	{
		for (int j = v; j <= y; j++)
		{
			for (int i = u; i <= (x + u) / 2; i++)
			{
				swap(a[i][j], a[x + u - i][j]);
			}
		}
	}
}
signed main()
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	 cin >> z;
	for (int i = 1; i <= z; i++)
	{
		for (int j = 1; j <= z; j++)
		{
			cin >> a[i][j];
		}
	}
	cin >> n;
	for (int i = 1; i <= n; i++)cin >> stk[i];
	while (n > 1)
	{
		int op = stk[n - 5];
		if (op == 1)
		{
			int u = stk[n - 4], v = stk[n - 3];
			int l = stk[n - 2], d = stk[n - 1], r = stk[n];
			int x = u + l - 1, y = v + l - 1;
			int cnt = d / 90; cnt = (4 - cnt) % 4;
			rev(1, 1, z, z, r);
			rev(u, v, x, y, cnt);
		}
		else
		{
			int u = stk[n - 4], d = stk[n - 3];
			int l = stk[n - 2], r = stk[n - 1], o= stk[n];
			change(u, l, d, r, o);
		}
		n -= 6;
	}
	int row = 0, col = 0;
	int cnt = 0;
	for (int i = 1; i <= z; i++)
	{
		int flag = 0;
		for (int j = 1; j <= z; j++)
		{
			if (a[i][j] != '?')
			{
				flag = 1;
				cnt++;
				ans.push_back(a[i][j]);
			}
		}	
		if (flag)row++;
	}
	col = cnt / row;
	cout << row << ec << col << endl;
	for (int i = 0; i < cnt; i++)
	{
		cout << ans[i];
		if (i % col == col - 1)cout << endl;
	}
	
	return 0;
}