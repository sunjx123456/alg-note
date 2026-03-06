#include <bits/stdc++.h>
using namespace std;
#define int long long
#define N 500010
#define M 2001
#define ec ' '
#define one 1ll
//#define endl '\n'
const int mod = 998244353;
#define word "Patch is damaged."
#define inf 0x7f7f7f7f
int n, m;
string line[N], text[N];
int modify[N], pri[N];
pair<int, int> patch[N];
struct info
{
  int NN, MM, nn, mm;
};
info pinfo[N];
bool digit(char c) { return c <= '9' && c >= '0'; }
vector<string> var[N];
int lcnt = 0;
int pcnt = 0;
int delta = 0;
int vcnt = 0;
int nxtstate(char c, int sta)
{
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
    if (text[x + i] != v[i]) return 1;
  }
  return 0;
}
info getinfo(string s)
{
    for(char &c:s)
    {
      if (!digit(c)) c = ' ';
    }
    info res;
    stringstream ss(s);
    ss >> res.NN >> res.MM >> res.nn >> res.mm;
    return res;
}
bool solution(int i)
{
  vector<string> vM, vm;
  info& s = pinfo[i];
  s.NN += delta;
  if (s.NN < pinfo[i - 1].NN + pinfo[i - 1].MM) return 1;
  auto [x, y] = patch[i];
  for (int j = x + 1; j <= y;j++)
  {
    char c = line[j][0];
     if (c != '+' && c != '-' && c != ' ') 
     {
       return 1;
     }
     string ctt = line[j].substr(1);
     if (c != '+') vM.push_back(ctt);
     if (c != '-') vm.push_back(ctt);
  }
  if (vM.size() != s.MM || vm.size() != s.mm) return 1;
  int ans = inf;
   for (int del = -s.MM + 1; del <= s.MM - 1; del++)
       {
if (s.NN + del >= 1 && s.NN + del + s.MM - 1 <= n && s.NN + del >= pinfo[i - 1].NN + pinfo[i - 1].MM && !cmp(vM, s.NN + del))          
if (abs(del) < abs(ans)) ans = del;
       }
    if (ans == inf) return 1;
    var[++vcnt] = vm;
      for (int j = s.NN + ans; j < s.NN + s.MM + ans; j++) {
        modify[j] = vcnt;
      }
      s.NN += ans;
      delta += ans;
      return 0;
}
signed main()
{
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0);
    cin >> n;
    cin.ignore();
    for (int i = 1; i <= n;i++)
      getline(cin, text[i]);
    string input;
    while (getline(cin, input))
    {
      if (input[0] == '#') continue;
      if (input.empty()) break;
      else 
      {
        line[++lcnt] = input;
        if(input[0]=='@')
        {
          if (pcnt == 0) patch[++pcnt].first = lcnt;
          else patch[pcnt].second = lcnt- 1, patch[++pcnt].first = lcnt;
        }
       
      }
    }
    if(!pcnt)
    {
      cout << word << endl;
      return 0;
    }
    patch[pcnt].second = lcnt;
    for (int i = 1; i <= pcnt; i++)
    {
      auto [x, y] = patch[i];
      if(judge(line[x]))
      {
        cout << word << endl;
        return 0;
      }
      pinfo[i] = getinfo(line[x]);
    }
    for (int i = 1; i <= pcnt;i++)
    {
        if(solution(i))
        {
          cout << word << endl;
          return 0;
        }
    }
    for (int i = 1;i<=n;i++)
    {
      if (modify[i] == 0) cout << text[i] << endl;
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