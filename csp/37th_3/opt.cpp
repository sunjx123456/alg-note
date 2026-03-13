#include <bits/stdc++.h>
using namespace std;
#define int long long
#define N 300100
#define M 510
const int inf = 1e18, mod = 1e9 + 7;
#define ec ' '
int n;
#define map unordered_map//优化2
struct info
{
	int len;
	vector<string>vars;
};
int add(int a, int b)
{
	return (a + b >= mod) ? (a + b - mod) : a + b;
}//优化1
map<string, int>mp;
map<string, bool>vis;//是否动态
map<string, info>tabel;
map<string, int>cur;//时间戳
map<string, int>temp;
int getval(const string& x, int dfn)//优化3
{
	int val = 0;
	if (vis[x] == 0)return mp[x];
	else if (cur[x] == dfn)return temp[x];
	else
	{
		//const vector<string>& tmp = tabel[x].vars;
		
		const vector<string>&tmp = tabel[x].vars;//优化4
		for ( const string& y : tmp)
		{
			val=add(val, getval(y, dfn));
		}
		cur[x] = dfn;
		val += tabel[x].len;
		val %= mod;
		temp[x] = val;
	}
	return val;
}
string x, y,line;
vector<string>tmp;
signed main()
{
	cin >> n;
	cin.ignore();
	for (int i = 1; i <= n; i++)
	{
		
		getline(cin, line);
		int op;
		stringstream ss(line);
		ss >> op;
		if (op == 1)
		{
			 ss >> x;
			int val = 0;
			while (ss >> y)
			{
				if (y[0] == '$')
				{
					y.erase(0, 1);
					val = add(val, getval(y,i));
				}
				else
				{
					val = add(val, y.size());
				}
			}
			mp[x] = val;
			if (vis[x])vis[x] = 0;
		}
		else if (op == 2)
		{
			 ss >> x;
			if (vis[x] == 0)
			{
				vis[x] = 1;
			}
			tmp.clear();
			int len = 0;
			while (ss >> y)
			{
				if (y[0] == '$')//优化5
					y.erase(0, 1),tmp.push_back(y);
				else len=add(len,y.size());
			}
			tabel[x] = { len, tmp };
		}
		else
		{
			 ss >> x;
			cout << getval(x, i) << endl;
		}
	}
	return 0;
}
