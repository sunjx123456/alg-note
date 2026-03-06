#include <bits/stdc++.h>
using namespace std;
#define int long long
#define N 500010
#define M 2001
#define ec ' '
#define one 1ll
#define word "Patch is damaged."
//#define endl '\n'
const int mod = 998244353;
#define inf 0x7f7f7f7f
int n, m;
int vis[N], nxt[N];
string line[N];
pair<int, int> patch[N];
string text[N];
struct info {
  int NN, MM, nn, mm;
};
info pinfo[N];
bool digit(char c) {
  return c <= '9' && c >= '0';
}
int modify[N], pri[N];
vector<string> var[N];

int nxtstate(char c, int sta) {
  switch (sta) {
  case 1: return c == ' ' ? 2 : -1;
  case 2: return c == '-' ? 3 : -1;
  case 3: return c != '0' && digit(c) ? 4 : -1;
  case 4: return digit(c) ? 4 : c == ',' ? 5
                                         : -1;
  case 5: return c != '0' && digit(c) ? 6 : -1;
  case 6: return digit(c) ? 6 : c == ' ' ? 7
                                         : -1;
  case 7: return c == '+' ? 8 : -1;
  case 8: return c != '0' && digit(c) ? 9 : -1;
  case 9: return digit(c) ? 9 : c == ',' ? 10
                                         : -1;
  case 10: return c != '0' && digit(c) ? 11 : -1;
  case 11: return digit(c) ? 11 : c == ' ' ? 12
                                           : -1;
  case 12: return c== '@' ? 13 : -1;
  default: -1;
  }
  return -1;
}
bool judge(string s)
{
  if (s.size() <= 2) return 1;
  if (s[0] != '@' || s[1] != '@' || s.back() != '@') return 1;
  int sta = 1;
  for (int i = 2; i < s.size() - 1;i++)
  {
    sta = nxtstate(s[i],sta);
    if (sta == -1) return 1;
  }
  if (sta == 13) return 0;
  else return 1;
}
bool cmp(const vector<string>& v,int x)
{
  int mm = v.size();
  for (int i = 0; i < mm;i++)
  {
    if (line[x + i] != v[i]) return 1;
  }
  return 0;
}
signed main()
{
   ios::sync_with_stdio(0); 
    cin.tie(0); 
    cout.tie(0);
    cin >> n;
    cin.ignore();
    int lcnt = 0;
    while (getline(cin,line[++lcnt]))
    {
      if (line[lcnt].empty()) break;
    }
    for (int i = 1; i <= n;i++)
    {
      text[i] = line[i];
    }
    int pcnt = 0;
    for (int i = n + 1; i <= lcnt; i++)
     {
     
      if(line[i][0]=='@')
      {
        if (pcnt == 0) patch[++pcnt].first = i;
        else patch[pcnt].second = i - 1, patch[++pcnt].first = i;
      }
    }
    if(pcnt==0)
    {
        cout<<word<<endl;return 0;
    }
    patch[pcnt].second = lcnt-1;
    int vcnt = 0;
    int delta = 0;
    for (int i = 1; i <= pcnt; i++) {
      auto [x, y] = patch[i];
      if (judge(line[x])) {
        cout << word << endl;
        return 0;
      }
      for (char &c : line[x])
        if (!digit(c)) c = ' ';
      stringstream ss(line[x]);
      info& s = pinfo[i];
      ss >> s.NN >> s.MM >> s.nn >> s.mm;
      s.NN += delta;
      if (s.NN < pinfo[i - 1].NN + pinfo[i - 1].MM) {
        cout << word << endl;
        return 0;
      }
      vector<string> vM, vm;
      for (int j = x + 1; j <= y; j++) {
        char c = line[j][0];
        if(c=='#')continue;
        if (c != '+' && c != '-' && c != ' ') {
          cout << word << endl;
          return 0;
        }
       string ctt=line[j].substr(1);
        if (line[j][0] != '+')  vM.push_back(ctt);
        if (line[j][0] != '-')  vm.push_back(ctt);
      }
      if (vM.size() != s.MM || vm.size() != s.mm) {
        cout << word << endl;
        return 0;
      }
      int ans = inf;
      for (int del = -s.MM + 1; del <= s.MM - 1; del++)
       {
if (s.NN + del >= 1 && s.NN + del + s.MM - 1 <= n && s.NN + del >= pinfo[i - 1].NN + pinfo[i - 1].MM && !cmp(vM, s.NN + del))          
if (abs(del) < abs(ans)) ans = del;
        }
      
      if (ans == inf) {
        cout << word << endl;
        return 0;
      }
      var[++vcnt] = vm;
      for (int i = s.NN + ans; i < s.NN + s.MM + ans; i++) {
        modify[i] = vcnt;
      }
      s.NN += ans;
      delta += ans;
    }
    for (int i = 1;i<=n;i++)
    {
      if (modify[i] == 0) cout << line[i] << endl;
      if(modify[i])
      {
        if (pri[modify[i]]) continue;
        else 
        {
          pri[modify[i]] = 1;
          for (string s : var[modify[i]]) cout << s << endl;
        }
      }
    }
      return 0;

}