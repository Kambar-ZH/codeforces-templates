#include <bits/stdc++.h>

using namespace std;

#define pb(i)               push_back(i)
#define For(i, n)           for(int i = 0; i < n; ++i)
#define qFor(i, x, n)       for(int i = x; i < n; ++i)
#define rFor(i, n)          for(int i = n - 1; i >= 0; --i)
#define see                 cout << endl;
#define all(x)              (x).begin(),(x).end()
#define rall(x)             (x).rbegin(),(x).rend()

#define ld                  long double
#define pii                 pair<int, int>
#define vt                  vector
#define ll                  long long
#define endl                '\n'
#define sim template < class c
#define ris return * this
#define dor > debug & operator <<
#define eni(x) sim > typename \
enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge { c b, e; };
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0);
sim > char dud(...);
#define LOCAL
struct debug {
#ifdef LOCAL
~debug() { cerr << endl; }
eni(!=) cerr << boolalpha << i; ris; }
eni(==) ris << range(begin(i), end(i)); }
sim, class b dor(pair < b, c > d) {
ris << "(" << d.first << ", " << d.second << ")";
}
sim dor(rge<c> d) {
*this << "[";
for (auto it = d.b; it != d.e; ++it)
    *this << ", " + 2 * (it == d.b) << *it;
ris << "]";
}
#else
sim dor(const c&) { ris; }
#endif
};
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "


const int MAX = 1e9;
const int MOD = 1e9 + 7;
const int BINT = 32;
const int BLONG = 64;
const ll  INF = 1e18;
const ld  PI  = 3.14159265358979323846;
 
template<typename T>
void read(vt<T> & a) {
    For(i, a.size()) cin >> a[i];
}
template<typename T>
void print(vt<T> & a) {
    For(i, a.size()) cout << a[i] << " ";
    cout << endl;
}
template<typename T>
void print2(vt<vt<T> > & a) {
    For(i, a.size()) {
        For(j, a[i].size()) cout << a[i][j] << " ";
        cout << endl;
    }
}
template<typename T>
void read2(vt<vt<T> > & a) {
    For(i, a.size()) For(j, a[i].size()) cin >> a[i][j];
}

const int N = 1e5 + 1e4;
const int L = 20;
vt<int> p(N, -1);
vt<int> val(N);
vt<vt<int> > dp(N, vt<int> (L, -1));
vt<vt<int> > dp_min(N, vt<int> (L, MAX));
vt<vt<int> > dp_max(N, vt<int> (L, -MAX));
vt<int> in(N), out(N);
int T = 0;

void dfs(int v, int par, int value, vt<vt<pii> > & g) {
    in[v] = ++T;
    p[v] = par;
    val[v] = value;
    for (pii pr : g[v]) {
        int u = pr.first;
        int w = pr.second;
        if (u == par) continue;
        dfs(u, v, w, g);
    }
    out[v] = T;
}

void find_parents() {
    for (int i = 0; i < N; i++) {
        if (p[i] == -1) continue;
        dp[i][0] = p[i];
        dp_max[i][0] = val[i];
        dp_min[i][0] = val[i];
    }
    for (int l = 1; l < L; l++) {
        for (int i = 0; i < N; i++) {
            int par = dp[i][l - 1];
            if (par != -1) {
                dp[i][l] = dp[par][l - 1];
                dp_max[i][l] = max(dp_max[i][l - 1], dp_max[par][l - 1]);
                dp_min[i][l] = min(dp_min[i][l - 1], dp_min[par][l - 1]);
            }
        }
    }
}

bool is_par(int v, int p) {
    return in[p] <= in[v] && out[v] <= out[p];
}

int lca(int node1, int node2) {
    if (is_par(node2, node1)) {
        return node1;
    }
    if (is_par(node1, node2)) {
        return node2;
    }
    for (int i = L - 1; i >= 0; i--) {
        int par = dp[node1][i];
        if (par == -1) continue;
        if (!is_par(node2, par)) {
            node1 = par;
        }
    }
    return p[node1];
}

pii ans(int node, int stop) {
    int mn = MAX, mx = -MAX;
    if (node == stop) {
        return {mn, mx};
    }
    for (int i = L - 1; i >= 0; i--) {
        int par = dp[node][i];
        if (par == -1) continue;
        if (!is_par(stop, par)) {
            mn = min(mn, dp_min[node][i]);
            mx = max(mx, dp_max[node][i]);
            node = par;
        }
    }
    mn = min(mn, dp_min[node][0]);
    mx = max(mx, dp_max[node][0]);
    return {mn, mx};
}

void clear(int n)
{
    T = 0;
    for (int i = 0; i < n; i++) {
        p[i] = 0;
        val[i] = 0;
        in[i] = 0;
        out[i] = 0;
        for (int l = 0; l < L; l++) {
            dp[i][l] = -1;
            dp_min[i][l] = MAX;
            dp_max[i][l] = -MAX;
        }
    }
}

void solve()
{
    
}

void precalc()
{
    
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef DEBUG
    freopen("output.txt", "w", stdout);
    freopen("input.txt", "r", stdin);
#endif
    int T;
    T = 1;
    cin >> T;
    precalc();
    For(t, T) solve();
    return 0;
}