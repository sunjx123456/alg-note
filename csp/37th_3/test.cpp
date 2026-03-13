#include <bits/stdc++.h>
using namespace std;
#define int long long
#define N 300100
#define M 510
const int inf = 1e18,mod=1e9+7;
#define ec ' '
int n;
map<string,int>mp;
map<string, bool>vis;//是否动态
map<string, vector<string>>tabel;
map<string, int>cur;//时间戳
map<string, int>temp;
int getval(string x,int dfn)
{
	int val = 0;
	if (vis[x] == 0)return mp[x];
	else if (cur[x] == dfn)return temp[x];
	else
	{
		vector<string> tmp = tabel[x];
		for (string y : tmp)
		{
			if (y[0] == '$')
			{
				string z = y.substr(1);
				//cout << z << endl;
				if (vis[z] == 0)val += mp[z], val %= mod;
				else if (cur[z]!=dfn)
				{
				    int m = getval(z,dfn);
					val += m;
					val %= mod;
					cur[z] = dfn;
					temp[z] = m;
				}
				else
				{
					val += temp[z];
					val %= mod;
				}
			}
			else val += y.size(),val%=mod;
		}
		
	}
	return val;
}
signed main()
{
	cin >> n;
	cin.ignore();
	for (int i = 1; i <= n; i++)
	{
		string line;
		getline(cin, line);
		int op; 
		stringstream ss(line);
		ss >> op;
		if (op == 1)
		{
			string x; ss >> x;
			
			string y;
			int val = 0;
			while (ss >> y)
			{
				if (y[0] == '$')
				{
					y.erase(0, 1);
					val += getval(y,i);
					val %= mod;
				}
				else
				{
					val += y.size();
					val %= mod;
				}
			}
			mp[x] = val;
			if (vis[x])vis[x] = 0;
		}
		else if (op == 2)
		{
			string x; ss >> x;
			if (vis[x]==0)
			{
				vis[x] = 1;	
			}
			vector<string>tmp;
			string y;
			while (ss >> y)
			{
				tmp.push_back(y);
			}
			tabel[x] = tmp;
		}
		else
		{
			string x; ss >> x;
			cout << getval(x,i) << endl;
		}
	}
	return 0;
}
