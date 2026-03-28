#include<bits/stdc++.h>
using namespace std;
int n, m;
#define N 1000110
int nex[N];
signed main()
{
	string s, c;
	cin >> c >> s;
	nex[0] = -1;
	nex[1] = 0;
	n = s.length();
	m = c.length();
	int j = 0;
	nex[0] = -1; nex[1] = 0;
	for (int i = 2; i <= n; i++)
	{
		while (j > 0 && s[i - 1] != s[j])
		{
			j = nex[j];
		}
		if (s[i - 1] == s[j])nex[i] = ++j;

	}
	j = 0;
	for (int i = 0; i < m; i++)
	{
		while (j > 0 && s[j] != c[i])
		{
			j = nex[j];
		}
		if (s[j] == c[i])j++;
		if (j == n)
		{
			cout << i - n + 2 << endl;
			j = nex[j];
		}
	}
	for (int i = 1; i <= n; i++)cout << nex[i] << ' ';
	return 0;
}