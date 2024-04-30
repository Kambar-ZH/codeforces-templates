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

struct graph {
    int n, m, timer, max_color;
    vt<int> tin, up, cut_points, components;
    vt<vt<pair<int, vt<int> > > > g;

    graph(vt<vt<pii> > & _g, int _m) {
        this->timer = 0;
        this->max_color = 0;
        this->n = _g.size();
        this->m = _m;
        this->tin.resize(n);
        this->up.resize(n);
        this->components.resize(m);
        this->normalize_graph(_g);
    };

    void normalize_graph(vt<vt<pii> > & _g) {
        this->g.resize(n);
        For(v, this->n) {
            sort(all(_g[v]));
            for (int i = 0; i < _g[v].size(); i++) {
                if (_g[v][i].first == v) continue;
                vt<int> ids = {_g[v][i].second};
                while (i + 1 < _g[v].size() && _g[v][i].first == _g[v][i + 1].first) {
                    i++;
                    ids.push_back(_g[v][i].second);
                }
                this->g[v].emplace_back(_g[v][i].first, ids);
            }
        }
    }

    void dfs(int v, int p, vt<bool> & visited) {
        visited[v] = 1;
        tin[v] = up[v] = timer++;
        int cnt = (p != -1);
        for (auto [u, _] : g[v]) {
            if (u == p) continue;
            if (visited[u]) {
                up[v] = min(up[v], tin[u]);
                continue;
            }
            dfs(u, v, visited);
            if (tin[v] <= up[u]) {
                cnt++;
            } else {
                up[v] = min(up[v], up[u]);
            }
        }
        if (cnt > 1) {
            cut_points.push_back(v);
        }
    }

    void find_cut_points() {
        vt<bool> visited(n);
        for (int v = 0; v < n; v++) {
            if (!visited[v]) {
                dfs(v, -1, visited);
            }
        }
    }

    void paint(int v, int p, int color, vt<bool> & visited) {
        visited[v] = true;

        for (auto [u, ids] : g[v]) {
            if (u == p) continue;
            if (!visited[u]) {
                int c = color;
                if (up[u] >= tin[v]) {
                    c = (++max_color);
                }
                for (int id : ids) {
                    components[id] = c;
                }

                paint(u, v, c, visited);
            } else if (tin[u] < tin[v]) {
                for (int id : ids) {
                    components[id] = color;
                }
            }
        }
    }

    void get_components() {
        vt<bool> visited(n);
        for (int v = 0; v < n; v++) {
            if (!visited[v]) {
                paint(v, -1, ++max_color, visited);
            }
        }
        squeeze();
    }

    void squeeze() {
        unordered_map<int, int> colors;
        int color = 0;
        for (int i = 0; i < m; i++) {
            if (colors[components[i]] == 0) {
                colors[components[i]] = ++color;
            }
            components[i] = colors[components[i]];
        }

        max_color = color;
    }
};

void solve() {
    int n, m; cin >> n >> m;
    vt<vt<pii> > g(n);
    For(i, m) {
        int u, v; cin >> u >> v; u--, v--;
        g[u].emplace_back(v, i);
        g[v].emplace_back(u, i);
    }
    graph gr = graph(g, m);
    gr.find_cut_points();
    print(gr.cut_points);

    gr.get_components();
    cout << gr.max_color << endl;
    print(gr.components);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}