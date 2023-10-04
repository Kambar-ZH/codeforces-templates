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

enum DP_POL { SUM, MIN, MAX, OR };

template <DP_POL dp_pol>
struct lca_tree {
    int N, L;
    vt<int> par, val;
    vt<vt<int> > dp_par, dp_val;
    vt<int> in, out;
    int T;
    lca_tree(int _N) {
        N = _N;
        L = log2(N) + 2;
        par = vt<int> (N, -1);
        val = vt<int> (N);
        depth = vt<int> (N);
        dp_par = vt<vt<int> >(N, vt<int> (L, -1));
        if constexpr (dp_pol == MIN) {
            dp_val = vt<vt<int> >(N, vt<int> (L, INT_MAX));
        } else if constexpr (dp_pol == MAX) {
            dp_val = vt<vt<int> >(N, vt<int> (L, -INT_MAX));
        } else if constexpr (dp_pol == SUM) {
            dp_val = vt<vt<int> >(N, vt<int> (L, 0));
        } else if constexpr (dp_pol == OR) {
            dp_val = vt<vt<int> >(N, vt<int> (L, 0));
        }
        in = vt<int> (N), out = vt<int> (N);
        T = 0;
    }

    void dfs(int v, int p, int value, vt<vt<pii> > & g) {
        in[v] = ++T;
        par[v] = p;
        val[v] = value;
        if (p != -1) {
            depth[v] = depth[p] + 1;
        }
        for (pii pr : g[v]) {
            int u = pr.first;
            int w = pr.second;
            if (u == p) continue;
            dfs(u, v, w, g);
        }
        out[v] = T;
    }

    void find_parents() {
        for (int i = 0; i < N; i++) {
            if (par[i] == -1) continue;
            dp_par[i][0] = par[i];
            dp_val[i][0] = val[i];
        }
        for (int l = 1; l < L; l++) {
            for (int i = 0; i < N; i++) {
                int par = dp_par[i][l - 1];
                if (par != -1) {
                    dp_par[i][l] = dp_par[par][l - 1];
                    if constexpr (dp_pol == MIN) {
                        dp_val[i][l] = min(dp_val[i][l - 1], dp_val[par][l - 1]);
                    } else if constexpr (dp_pol == MAX) {
                        dp_val[i][l] = max(dp_val[i][l - 1], dp_val[par][l - 1]);
                    } else if constexpr (dp_pol == SUM) {
                        dp_val[i][l] = dp_val[i][l - 1] + dp_val[par][l - 1];
                    } else if constexpr (dp_pol == OR) {
                        dp_val[i][l] = dp_val[i][l - 1] | dp_val[par][l - 1];
                    }
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
            int par = dp_par[node1][i];
            if (par == -1) continue;
            if (!is_par(node2, par)) {
                node1 = par;
            }
        }
        return par[node1];
    }

    int ans(int node, int stop) {
        int val = 0;
        if constexpr (dp_pol == MIN) {
            val = INT_MAX;
        } else if constexpr (dp_pol == MAX) {
            val = -INT_MAX;
        } else if constexpr (dp_pol == SUM) {
            val = 0;
        } else if constexpr (dp_pol == OR) {
            val = 0;
        }
        if (node == stop) {
            return val;
        }
        for (int i = L - 1; i >= 0; i--) {
            int par = dp_par[node][i];
            if (par == -1) continue;
            if (!is_par(stop, par)) {
                if constexpr (dp_pol == MIN) {
                    val = min(val, dp_val[node][i]);
                } else if constexpr (dp_pol == MAX) {
                    val = max(val, dp_val[node][i]);
                } else if constexpr (dp_pol == SUM) {
                    val = val + dp_val[node][i];
                } else if constexpr (dp_pol == OR) {
                    val = val | dp_val[node][i];
                }
                node = par;
            }
        }
        if constexpr (dp_pol == MIN) {
            val = min(val, dp_val[node][0]);
        } else if constexpr (dp_pol == MAX) {
            val = max(val, dp_val[node][0]);
        } else if constexpr (dp_pol == SUM) {
            val = val + dp_val[node][0];
        } else if constexpr (dp_pol == OR) {
            val = val | dp_val[node][0];
        }
        return val;
    }

    void clear(int n) {
        T = 0;
        for (int i = 0; i < n; i++) {
            par[i] = 0;
            val[i] = 0;
            in[i] = 0;
            out[i] = 0;
            for (int l = 0; l < L; l++) {
                dp_par[i][l] = -1;
                dp_val[i][l] = 0;
            }
        }
    }
};

void solve() 
{
    int n, m; cin >> n >> m;
    vt<vt<pii> > g(n);
    For(i, m) {
        int u, v, w; cin >> u >> v >> w; u--, v--;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    lca_tree tree = lca_tree<DP_POL::MIN>(2e5 + 2e4);
    tree.dfs(0, -1, 0, g);
    tree.find_parents();
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