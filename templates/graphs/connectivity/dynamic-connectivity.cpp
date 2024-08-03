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

struct dsu_persistent {
    vt<int> par, rank;
    vt<pair<int*, int>> hist;
    int components;

    dsu_persistent() {}

    dsu_persistent(int n) {
        this->par = vt<int> (n, -1);
        this->rank = vt<int> (n, 0);
        this->components = n;
    }

    int find(int u) {
        while (par[u] != -1) {
            u = par[u];
        }
        return u;
    }

    bool merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) {
            return false;
        }
        if (rank[u] > rank[v]) {
            hist.emplace_back(&par[v], par[v]);
            par[v] = u;
        } else if (rank[u] < rank[v]) {
            hist.emplace_back(&par[u], par[u]);
            par[u] = v;
        } else {
            hist.emplace_back(&par[u], par[u]);
            hist.emplace_back(&rank[v], rank[v]);
            par[u] = v;
            ++rank[v];
        }
        components++;
        return true;
    }

    void rollback(int back_to) {
        while ((int)hist.size() > back_to) {
            *hist.back().first = hist.back().second;
            hist.pop_back();
            components--;
        }
    }
};

struct dynamic_connectivity {
    struct query {
        int type, u, v;
        bool ans;
    };

    int n, q_cnt; 
    dsu_persistent dsu;
    vt<query> queries;
    vt<vt<pii> > tree;

    dynamic_connectivity() {}
    
    dynamic_connectivity(int n, int q_cnt) {
        this->n = n;
        this->q_cnt = q_cnt;
        this->dsu = dsu_persistent(n);
        this->queries = vt<query> (q_cnt);
        this->tree = vt<vt<pii> > (q_cnt << 2);
    }

    void input() {
        set<pair<pii, int> > edges;
        for (int i = 0; i < q_cnt; ++i) {
            string op; cin >> op;
            // handle query type
            if (op == "add") {
                queries[i].type = 1;
            } else if (op == "rem") {
                queries[i].type = 2;
            } else {
                queries[i].type = 3;
            }
            cin >> queries[i].u >> queries[i].v;
            if (queries[i].u > queries[i].v) swap(queries[i].u, queries[i].v);
            if (queries[i].type == 1) {
                edges.emplace(pii(queries[i].u, queries[i].v), i);
            }
            else if (queries[i].type == 2) {
                auto iter = edges.lower_bound(make_pair(pii(queries[i].u, queries[i].v), 0));
                add_edge(iter->second, i, iter->first);
                edges.erase(iter);
            }
        }
        // handle not deleted edges
        for (auto e : edges) {
            add_edge(e.second, q_cnt - 1, e.first);
        }
    }

    void _add_edge(int l, int r, pii uv, int x, int lx, int rx) {
        if (l > rx || r < lx)
            return;
        if (l <= lx && rx <= r) {
            tree[x].push_back(uv);
            return;
        }
        int mid = (lx + rx) >> 1;
        _add_edge(l, r, uv, ls(x), lx, mid);
        _add_edge(l, r, uv, rs(x), mid+1, rx);
    }

    void add_edge(int l, int r, pii uv) {
        return _add_edge(l, r, uv, 0, 0, q_cnt - 1);
    }

    void _go(int x, int lx, int rx) {
        int startSize = dsu.hist.size();
        for (pii uv : tree[x])
            dsu.merge(uv.first, uv.second);

        if (lx == rx) {
            if (queries[lx].type == 3) {
                queries[lx].ans = (dsu.find(queries[lx].u) == dsu.find(queries[lx].v));
            }
        } else {
            int mid = (lx + rx) / 2;
            _go(ls(x), lx, mid);
            _go(rs(x), mid+1, rx);
        }

        dsu.rollback(startSize);
    }

    void go() {
        return _go(0, 0, q_cnt - 1);
    }

    vt<bool> get_ans() {
        vt<bool> ans;
        for (int i = 0; i < q_cnt; i++) {
            if (queries[i].type == 3) {
                ans.push_back(queries[i].ans);
            }
        }
        return ans;
    }
};

void solve() {
    int n, q_cnt; cin >> n >> q_cnt;
    dynamic_connectivity dc = dynamic_connectivity(n, q_cnt);
    dc.input();
    dc.go();
    vt<bool> ans = dc.get_ans();
    for (bool x : ans) {
        if (x) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}