#include <bits/stdc++.h>

using namespace std;

#define For(i, n)           for(int i = 0; i < n; ++i)
#define qFor(i, x, n)       for(int i = x; i < n; ++i)
#define all(x)              (x).begin(),(x).end()
#define rall(x)             (x).rbegin(),(x).rend()

#define ld                  long double
#define pii                 pair<int, int>
#define vt                  vector
#define ll                  long long
#define endl                '\n'

#define DEBUG
#ifdef DEBUG
#define dout(str)           do {cout << str;} while(false)
#else
#define dout(str)           do { } while ( false )
#endif

const int MAX = 1e9;
const int MOD = 1e9 + 7;
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

const int N = 2e5 + 5;
const int L = 20;
vt<vt<int> > up(N, vt<int> (L));
int timer = 0;
vt<int> tin(N), tout(N);
vt<int> par(N);


void dfs(int v, int p, vt<vt<int> > & g) {
    if (p != -1) {
        par[v] = p;
    }
    tin[v] = timer++;
    bool leaf = true;
    for (int u : g[v]) {
        if (u == p) continue;
        dfs(u, v, g);
    }
    tout[v] = timer++;
}

bool is_ancestor(int cur, int par) {
    return tin[cur] > tin[par] && tout[par] > tout[cur];
}

void precalc(int n) {
    for (int i = 0; i < n; i++) {
        up[i][0] = par[i];
    }
    for (int l = 1; l < L; l++) {
        for (int i = 0; i < n; i++) {
            up[i][l] = up[up[i][l - 1]][l - 1];
        }
    }
}

int binary_lifting(int v, int u) {
    if (is_ancestor(v, u)) {
        return u;
    }
    if (is_ancestor(u, v)) {
        return v;
    }
    for (int i = L - 1; i >= 0; i--) {
        if (!is_ancestor(u, up[v][i])) {
            v = up[v][i];
        }
    }
    return up[v][0];
}

int k_th_parent(int v, int k) {
    if (k == 0) {
        return v;
    }
    for (int i = L - 1; i >= 0; i--) {
        if (k >= (1 << i)) {
            k -= (1 << i);
            v = up[v][i];
        }
    }
    return v;
}

void solve()
{
    int n; cin >> n;
    vt<vt<int> > g(n);
    dfs(0, -1, g);
    precalc(n);
}
 
int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
// #define FILE
#ifdef FILE
    freopen("output.txt", "w", stdout);
    freopen("input.txt", "r", stdin);
#endif
    cout << setprecision(20) << fixed;
    int T = 1;
    cin >> T;
    For(t, T) {
        solve();
    }
    return 0;
}