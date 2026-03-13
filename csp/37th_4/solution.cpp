#include <bits/stdc++.h>
using namespace std;
#define int long long
#define N 1000100
#define M 510
const int inf = 1e18, mod = 998244353;
#define ec ' '
int n;
int a[N];
struct block
{
	int val; int l, r;
	int cal()const
	{
		return (l + r) * (r - l + 1) / 2%mod;
	}
};
vector<block>var;
vector<block>tmp;
signed main()
{
	ios::sync_with_stdio(0); cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++)cin >> a[i];
	int ans = 0;
	ans += a[1];
	var.push_back({ a[1],1,1 });
	for (int i = 2; i <= n; i++)
	{
		for (int j = var.size() - 1; j >=0; j--)
		{
			var[j].val = gcd(var[j].val, a[i]);
		}
		var.push_back({ a[i],i,i });
		//tmp.clear();
		//for (const block& x : var)
		//{
		//	if (tmp.empty())tmp.push_back(x);
		//	else if (x.val == tmp.back().val)
		//	{
		//		tmp.back().r = x.r;
		//	}
		//	else
		//	{
		//		tmp.push_back(x);
		//	}
		//}
		//var.swap(tmp);//用swap交换指针O(1)
		int k = 0;
		for (int j = 1; j < var.size(); j++)
		{
			if (var[j].val == var[k].val)var[k].r = var[j].r;
			else var[++k] = var[j];
		}
		var.resize(k + 1);
		for (const block& x : var)
		{
			ans += (i * x.val)%mod * x.cal()%mod;
			ans %= mod;
		}
	}
	cout << ans;
	return 0;
}