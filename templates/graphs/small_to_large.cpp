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

template<typename T> void read(vt<T> & a) {For(i, a.size()) cin >> a[i];}
template<typename T> void read2(vt<vt<T> > & a) {For(i, a.size()) read(a[i]);}
template<typename T> void print(vt<T> & a) {For(i, a.size()) cout << a[i] << " "; cout << endl;}
template<typename T> void print2(vt<vt<T> > & a) {For(i, a.size()) print(a[i]);}

const int MAX = 1e9;
const int MOD = 1000000007;
const ll  INF = 1e18;
const ld  PI  = 3.14159265358979323846;

struct SmallToLarge {
    int timer = 0;
    vt<int> sz, tin, tout, ver;
    vt<int> ans;
    vt<vt<int> > g;
    
    SmallToLarge(
        int n,
        vt<vt<int> > g
    ) {
        this->g = g;
        this->sz.resize(n);
        this->tin.resize(n);
        this->tout.resize(n);
        this->precalc();
    }

    void _precalc(int u, int p) {
        sz[u] = 1;
        ver.push_back(u);
        tin[u] = timer++;
        for (int to : g[u]) {
            if (to == p) continue;
            _precalc(to, u);
            sz[u] += sz[to];
        }
        tout[u] = timer-1;
    }

    void precalc() {
        _precalc(0, -1);
    }

    void add(int u) {
        
    }

    void remove(int u) {
        
    }

    // clear calculations over subtree
    void clear() {

    }

    void calc_ans(int u) {
        ans[u];
    };

    void _dfs(int u, int p, bool keep) {
        int big_child = -1;
        for (int to : g[u]) {
            if (to == p) continue;
            if (big_child == -1 || sz[big_child] < sz[to]) {
                big_child = to;
            }
        }
        for (int to : g[u]) {
            if (to == p || to == big_child) continue;
            _dfs(to, u, false);
        }
        if (big_child != -1) {
            _dfs(big_child, u, true);
        }
        for (int to : g[u]) {
            if (to == p || to == big_child) continue;
            for (int i = tin[u]; i <= tout[u]; i++) {
                add(ver[i]);
            }
        }
        add(u);
        
        // process queries over subree of 'u' here
        calc_ans(u);

        if (!keep) {
            for (int i = tin[u]; i <= tout[u]; i++) {
                remove(ver[i]);
                clear();
            }
        }
    };
    
    void dfs() {
        _dfs(0, -1, true);
    }
};

void solve() {
    int n; cin >> n;
    vt<vt<int> > g(n);
    SmallToLarge stl = SmallToLarge(n, g);
    stl.dfs();
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}