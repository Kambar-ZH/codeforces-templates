#include <bits/stdc++.h>

using namespace std;

#define For(i, n)           for(int i = 0; i < n; ++i)
#define all(x)              (x).begin(),(x).end()
#define rall(x)             (x).rbegin(),(x).rend()
#define ls(x)               x+x+1
#define rs(x)               x+x+2
#define endl                '\n'

#define ld                  long double
#define pii                 pair<int, int>
#define vt                  vector
#define ll                  long long

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

template<typename T>
void read(vt<T> & a) {For(i, a.size()) cin >> a[i];}
template<typename T>
void read2(vt<vt<T> > & a) {For(i, a.size()) read(a[i]);}
template<typename T>
void print(vt<T> & a) {For(i, a.size()) cout << a[i] << " "; cout << endl;}
template<typename T>
void print2(vt<vt<T> > & a) {For(i, a.size()) print(a[i]);}

const int MAX = 1e9;
const int MOD = 998244353;
const ll  INF = 1e18;
const ld  PI  = 3.14159265358979323846;

struct tree {
    int N, L;
    vt<int> par, depth;
    vt<vt<int> > dp_par; // dp_par[0] is itself
    int timer;
    vt<int> in, out;

    tree(int N) {
        this->N      = N;
        this->L      = log2(N) + 2;
        this->par    = vt<int> (N, -1);
        this->depth  = vt<int> (N);
        this->in     = vt<int> (N);
        this->out    = vt<int> (N);
        this->timer  = 0;
    }

    void dfs(int v, int p, vt<vt<int> > & g) {
        in[v] = ++timer;
        par[v] = p;
        if (p != -1) {
            depth[v] = depth[p] + 1;
        }

        for (int u : g[v]) {
            if (u == p) continue;
            dfs(u, v, g);
        }

        out[v] = timer;
    }

    void calc_dp_par() {
        dp_par = vt<vt<int> >(N, vt<int> (L, -1));

        for (int i = 0; i < N; i++) {
            dp_par[i][0] = i;
            dp_par[i][1] = par[i];
        }

        for (int l = 2; l < L; l++) {
            for (int i = 0; i < N; i++) {
                int par = dp_par[i][l - 1];
                if (par != -1) {
                    dp_par[i][l] = dp_par[par][l - 1];
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

        for (int i = L - 1; i >= 1; i--) {
            int par = dp_par[node1][i];
            if (par == -1) continue;
            if (!is_par(node2, par)) {
                node1 = par;
            }
        }

        return par[node1];
    }
};

struct auxiliary_tree {
    vt<vt<int> > g;
    vt<int> auxiliary_vertices;
    vt<int> important_vertices;
    unordered_map<int, bool> is_important;

    auxiliary_tree() {}

    auxiliary_tree(vt<vt<int> > g, vt<int> auxiliary_vertices, vt<int> important_vertices) {
        this->g = g;
        this->auxiliary_vertices = auxiliary_vertices;
        this->important_vertices = important_vertices;
        this->fill_is_important();
    }

    void fill_is_important() {
        for (int v : important_vertices) {
            is_important[v] = true;
        }
    }

    // tree is zero rooted
    int root() {
        return 0;
    }

    // returns original vertex index
    int vertex(int v) {
        return auxiliary_vertices[v];
    }
};

struct tree_auxiliarator {
    int n;
    vt<vt<int> > g;

    tree_auxiliarator() {}

    tree_auxiliarator(vt<vt<int> > g) {
        this->n = g.size();
        this->g = g;
    }

    auxiliary_tree auxiliarate(vt<int> important_vertices) {
        tree t = tree(n);
        t.dfs(0, -1, g);
        t.calc_dp_par();
        vt<int> auxiliary_vertices = important_vertices;
        int sz = auxiliary_vertices.size();
        if (sz == 0) return auxiliary_tree();
        sort(all(auxiliary_vertices), [&] (int x, int y) {
            return t.in[x] < t.in[y];
        });
        for (int j = 0; j < sz - 1; j++) {
            int x = auxiliary_vertices[j], y = auxiliary_vertices[j + 1];
            auxiliary_vertices.push_back(t.lca(x, y));
        }
        sort(all(auxiliary_vertices), [&] (int x, int y) {
            return t.in[x] < t.in[y];
        });
        auxiliary_vertices.erase(unique(all(auxiliary_vertices)),auxiliary_vertices.end());
        vt<int> st = {0};
        sz = auxiliary_vertices.size();
        vt<vt<int> > auxiliary_g(sz);
        for (int j = 1; j < sz; j++) {
            while (!t.is_par(auxiliary_vertices[j], auxiliary_vertices[st.back()])) {
                st.pop_back();
            }
            auxiliary_g[st.back()].push_back(j);
            st.push_back(j);
        }
        return auxiliary_tree(auxiliary_g, auxiliary_vertices, important_vertices);
    }
};

void solve() {
    int n; cin >> n;
    vt<int> color(n); read(color);
    vt<vt<int> > g(n);
    For(i, n - 1) {
        int x, y; cin >> x >> y; x--, y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    tree_auxiliarator ti
}

// Problem:
// https://atcoder.jp/contests/abc340/tasks/abc340_g

// THE SOLUTION IS ALWAYS SIMPLE
// THE CODE IS ALWAYS SHORT

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef DEBUG
    freopen("output.txt", "w", stdout);
    freopen("input.txt", "r", stdin);
#endif
    int T = 1;
    For(t, T) solve();
    return 0;
}