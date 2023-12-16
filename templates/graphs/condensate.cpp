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

struct graph {
    int n, m, max_color;
    vt<int> post_order, components;
    vt<vt<int> > g, gr;

    graph(int _n, vt<pii> & _edges) {
        this->max_color = 0;
        this->n = _n;
        this->components.resize(n);
        this->build_graph(_edges);
    };

    void build_graph(vt<pii> & _edges) {
        this->g.resize(n);
        this->gr.resize(n);
        for (auto & [u, v] : _edges) {
            g[u].push_back(v);
            gr[v].push_back(u);
        }
    }

    void dfs(int v, vt<bool> & visited) {
        visited[v] = 1;
        for (int u : g[v]) {
            if (visited[u]) continue;
            dfs(u, visited);
        }
        post_order.push_back(v);
    }

    void dfs() {
        vt<bool> visited(n);
        for (int v = 0; v < n; v++) {
            if (visited[v]) continue; 
            dfs(v, visited);
        }
    }

    void condensate(int v, int color, vt<bool> & visited) {
        visited[v] = 1;
        components[v] = color;
        for (int u : gr[v]) {
            if (visited[u]) continue;
            condensate(u, color, visited);
        }
    }

    void condensate() {
        dfs();
        reverse(all(post_order));
        vt<bool> visited(n);
        for (int v : post_order) {
            if (visited[v]) continue;
            condensate(v, ++max_color, visited);
        }
    }
};

void solve() {
    int n, m; cin >> n >> m;
    vt<pii> edges;
    For(i, m) {
        int u, v; cin >> u >> v; u--, v--;
        edges.emplace_back(u, v);
    }
    graph gr = graph(n, edges);
    gr.condensate();
    
    print(gr.components);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}