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

template<typename T>
void read(vt<T> & a) {For(i, a.size()) cin >> a[i];}
template<typename T>
void read2(vt<vt<T> > & a) {For(i, a.size()) read(a[i]);}
template<typename T>
void print(vt<T> & a) {For(i, a.size()) cout << a[i] << " "; cout << endl;}
template<typename T>
void print2(vt<vt<T> > & a) {For(i, a.size()) print(a[i]);}

const int MAX = 1e9;
const int MOD = 1e9+7;
const ll  INF = 1e18;
const ld  PI  = 3.14159265358979323846;

struct lca_tree {
    int N, L;
    vt<int> par, val, depth;
    vt<vt<int> > dp_par, dp_val;
    int T;
    vt<int> in, out;

    lca_tree(int N) {
        this->N      = N;
        this->L      = log2(N) + 2;
        this->par    = vt<int> (N, -1);
        this->val    = vt<int> (N);
        this->depth  = vt<int> (N);
        this->dp_par = vt<vt<int> >(N, vt<int> (L, -1));
        this->dp_val = vt<vt<int> >(N, vt<int> (L, 0));
        this->in     = vt<int> (N);
        this->out    = vt<int> (N);
        this->T      = 0;
    }

    void dfs(int v, int p, vt<vt<int> > & g) {
        in[v] = ++T;
        par[v] = p;
        if (p != -1) {
            depth[v] = depth[p] + 1;
        }
        for (int u : g[v]) {
            if (u == p) continue;
            dfs(u, v, g);
        }
        out[v] = T;
    }

    void find_parents() {
        for (int i = 0; i < N; i++) {
            dp_val[i][0] = val[i];
            dp_val[i][1] = val[i];
            if (par[i] != -1) {
                dp_val[i][1] |= val[par[i]];
            }
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
        for (int l = 2; l < L; l++) {
            for (int i = 0; i < N; i++) {
                int par = dp_par[i][l - 1];
                if (par != -1) {
                    dp_val[i][l] = (dp_val[i][l - 1] | dp_val[par][l - 1]);
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

    int ans(int node, int k) {
        int val = 0;
        for (int i = L - 1; i >= 1; i--) {
            int par = dp_par[node][i];
            if (par == -1) continue;
            if (k & (1 << (i - 1))) {
                k -= (1 << (i - 1));
                val = val | dp_val[node][i];
                node = par;
            }
        }
        val = val | dp_val[node][0];
        return val;
    }

    int kth_par(int node, int k) {
        for (int i = L - 1; i >= 1; i--) {
            int par = dp_par[node][i];
            if (par == -1) continue;
            if (k & (1 << (i - 1))) {
                k -= (1 << (i - 1));
                node = par;
            }
        }
        return node;
    }
};

void solve() {
    int n, m; cin >> n >> m;
    vt<int> val(n); read(val);
    vt<vt<int> > g(n);
    For(i, m) {
        int u, v, w; cin >> u >> v >> w; u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    lca_tree tree = lca_tree(n);
    tree.dfs(0, -1, g);
    tree.val = val;
    tree.find_parents();
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}