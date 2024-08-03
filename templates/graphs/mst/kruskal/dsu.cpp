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

struct DSU {
    int n, components_cnt;
    vt<int> par, sz;

    DSU(int n) {
        this->n = n;
        components_cnt = n;
        par = vt<int> (n); iota(all(par), 0);
        sz = vt<int> (n, 1);
    }

    int find(int v) {
        if (par[v] == v) {
            return v;
        }

        return par[v] = find(par[v]);
    }

    bool merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) {
            return false;
        }

        components_cnt--;
        if (sz[v] > sz[u]) {
            par[u] = v;
            sz[v] += sz[u];
        } else {
            par[v] = u;
            sz[u] += sz[v];
        }

        return true;
    }

    bool is_connected() {
        return components_cnt == 1;
    }
};

void solve() {
    int n; cin >> n;
    DSU dsu = DSU(n);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}