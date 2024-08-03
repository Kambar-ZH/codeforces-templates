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

struct graph {
    int n, timer, max_color;
    vt<int> tin, up, bridges, components;
    vt<vt<pair<pii, bool> > > g;

    graph(vt<vt<pii> > & _g) {
        this->timer = 0;
        this->max_color = 0;
        this->n = _g.size();
        this->tin.resize(n);
        this->up.resize(n);
        this->components.resize(n);
        this->normalize_graph(_g);
    };

    void normalize_graph(vt<vt<pii> > & _g) {
        this->g.resize(n);
        For(v, this->n) {
            sort(all(_g[v]));
            for (int i = 0; i < _g[v].size(); i++) {
                if (_g[v][i].first == v) continue;
                bool dupl = false;
                while (i + 1 < _g[v].size() && _g[v][i].first == _g[v][i + 1].first) {
                    i++;
                    dupl = true;
                }
                this->g[v].emplace_back(_g[v][i], dupl);
            }
        }
    }

    void dfs(int v, int p, vt<bool> & visited) {
        visited[v] = true;
        tin[v] = up[v] = timer++;
        for (auto [pr, dupl] : g[v]) {
            int u = pr.first;
            int id = pr.second;
            if (u == p) continue;
            if (visited[u]) {
                up[v] = min(up[v], tin[u]);
                continue;
            }
            dfs(u, v, visited);
            if ((tin[v] < up[u]) && !dupl) {
                bridges.push_back(id);
            } else {
                up[v] = min(up[v], up[u]);
            }
        }
    }

    void find_bridges() {
        vt<bool> visited(n);
        for (int v = 0; v < n; v++) {
            if (!visited[v]) {
                dfs(v, -1, visited);
            }
        }
    }

    void paint(int v, int color, vt<bool> & visited) {
        visited[v] = true;
        components[v] = color;
        for (auto [pr, dupl] : g[v]) {
            int u = pr.first;
            if (visited[u]) continue;
            int c = color;
            if ((tin[v] < up[u]) && !dupl) {
                c = (++max_color);
            }
            paint(u, c, visited);
        }
    }

    void get_components() {
        vt<bool> visited(n);
        for (int v = 0; v < n; v++) {
            if (!visited[v]) {
                paint(v, ++max_color, visited);
            }
        }
    }
};

void solve() {
    int n, m; cin >> n >> m;
    vt<vt<pii> > g(n);
    For(i, m) {
        int u, v; cin >> u >> v; u--, v--;
        if (u == v) continue;
        g[u].emplace_back(v, i);
        g[v].emplace_back(u, i);
    }
    graph gr = graph(g);
    gr.find_bridges();
    print(gr.bridges);

    gr.get_components();
    cout << gr.max_color << endl;
    print(gr.components);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}