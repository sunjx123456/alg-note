#include <bits/stdc++.h>
using namespace std;template <typename A, typename B>ostream &operator<<(ostream &cout, const pair<A, B> &p) {return cout << '(' << p.first << ", " << p.second << ')';}template <typename Tp,typename T = typename enable_if<!is_same<Tp, string>::value,typename Tp::value_type>::type>ostream &operator<<(ostream &cout, const Tp &v) {cout << '{';string sep;for (const T &x : v) cout << sep << x, sep = ", ";return cout << '}';}void Output() { cerr << endl; }template <typename Head, typename... Tail>void Output(Head H, Tail... T) {cerr << ' ' << H;Output(T...);}
#ifdef LOCAL
#define ps cerr << "YES" << endl
#define debug(...) \
  cerr << "(" << #__VA_ARGS__ << "):" << endl, Output(__VA_ARGS__)
#else
#define ps 114514 
#define debug(...) 114514
#endif
// ----------------------------------------------------------------//
#define int long long
#define lowbit(i) ((i)&(-i))
#define rep(i, a, b) for(int i=a;i<=b;i++)
#define ll long long
#define endl "\n"
#define all(v) v.begin() + 1 , v.end()
typedef vector<int> vi ; typedef vector <vector <int > > vii ; typedef vector <pair <int , int > > vp ; typedef pair<int ,int > pii;
const int INF = 0x3f3f3f3f3f3f3f3f;
const int N = 2e5 + 10 , M = N * 2 ;
// ----------------------------------------------------------------//

void solve()
{
    int Z;
    if (!(cin >> Z)) return;
    vector<string> g(Z);
    rep(i, 0, Z - 1) cin >> g[i];

    int k; 
    cin >> k;
    vector<int> key(k);
    rep(i, 0, k - 1) cin >> key[i];

    int t = (k > 0 ? (int)key[0] : 0);
    vector<array<int, 6>> ops;
    ops.reserve(t);
    rep(i, 0, t - 1) {
        array<int, 6> cur{};
        rep(j, 0, 5) cur[j] = key[1 + i * 6 + j];
        ops.push_back(cur);
    }

    int rot = 0; // g = rotate_cw(A_current, rot)

    auto mapCoord = [&](int i, int j) -> pair<int, int> {
        if (rot == 0) return {i, j};
        if (rot == 1) return {j, Z - 1 - i};
        if (rot == 2) return {Z - 1 - i, Z - 1 - j};
        return {Z - 1 - j, i};
    };

    auto rotateSquareCCW = [&](int u, int v, int L, int times) {
        times %= 4;
        if (times < 0) times += 4;
        if (times == 0) return;
        vector<string> temp(L, string(L, '?'));
        rep(i, 0, L - 1) {
            rep(j, 0, L - 1) {
                auto [x, y] = mapCoord(u + i, v + j);
                temp[i][j] = g[x][y];
            }
        }
        rep(ti, 0, times - 1) {
            vector<string> nxt(L, string(L, '?'));
            rep(i, 0, L - 1) {
                rep(j, 0, L - 1) {
                    nxt[L - 1 - j][i] = temp[i][j];
                }
            }
            temp.swap(nxt);
        }
        rep(i, 0, L - 1) {
            rep(j, 0, L - 1) {
                auto [x, y] = mapCoord(u + i, v + j);
                g[x][y] = temp[i][j];
            }
        }
    };

    auto flipRect = [&](int u, int d, int l, int r, int o) {
        int h = d - u + 1;
        int w = r - l + 1;
        vector<string> temp(h, string(w, '?'));
        rep(i, 0, h - 1) {
            rep(j, 0, w - 1) {
                auto [x, y] = mapCoord(u + i, l + j);
                temp[i][j] = g[x][y];
            }
        }
        if (o == 1) {
            rep(i, 0, h / 2 - 1) {
                swap(temp[i], temp[h - 1 - i]);
            }
        } else {
            rep(i, 0, h - 1) {
                rep(j, 0, w / 2 - 1) {
                    swap(temp[i][j], temp[i][w - 1 - j]);
                }
            }
        }
        rep(i, 0, h - 1) {
            rep(j, 0, w - 1) {
                auto [x, y] = mapCoord(u + i, l + j);
                g[x][y] = temp[i][j];
            }
        }
    };

    for (int idx = t - 1; idx >= 0; idx--) {
        const auto &op = ops[idx];
        if (op[0] == 1) {
            int u = (int)op[1] - 1;
            int v = (int)op[2] - 1;
            int L = (int)op[3];
            int d = (int)op[4];
            int r = (int)op[5];
            rot = (rot - (r % 4) + 4) % 4;
            int times = (d / 90) % 4;
            rotateSquareCCW(u, v, L, times);
        } else {
            int u = (int)op[1] - 1;
            int d = (int)op[2] - 1;
            int l = (int)op[3] - 1;
            int r = (int)op[4] - 1;
            int o = (int)op[5];
            flipRect(u, d, l, r, o);
        }
    }

    vector<string> A0(Z, string(Z, '?'));
    rep(i, 0, Z - 1) {
        rep(j, 0, Z - 1) {
            auto [x, y] = mapCoord(i, j);
            A0[i][j] = g[x][y];
        }
    }

    int n = 0, m = 0;
    rep(i, 0, Z - 1) {
        rep(j, 0, Z - 1) {
            if (A0[i][j] != '?') {
                n = max(n, i + 1);
                m = max(m, j + 1);
            }
        }
    }

    cout << n << " " << m << endl;
    rep(i, 0, n - 1) {
        cout << A0[i].substr(0, m) << endl;
    }
}

signed main()
{
    ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    cout << fixed << setprecision(6) ; 
    int _ = 1;
    // cin>>_;
    while(_ -- )
    {
        solve();
    }
    return 0;
}