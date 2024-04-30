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

struct seg_tree_push {
	int n;
	vt<ll> tree, lazy;
    seg_tree_push() {}
	seg_tree_push(int n) {
		this->n = n;
		tree.resize(4 * n);
		lazy.resize(4 * n);
	}
 
	void push(int x) {
        tree[x] = (tree[x] + lazy[x]);
        lazy[ls(x)] = (lazy[ls(x)] + lazy[x]);
        lazy[rs(x)] = (lazy[rs(x)] + lazy[x]);
        lazy[x] = 0;
    }

    ll _get(int x, int lx, int rx, int l, int r) {
        push(x);

        if (l == lx && rx == r) {
            return tree[x];
        }

        int mx = (lx + rx) >> 1;
        
        if (r <= mx) {
            return _get(ls(x), lx, mx, l, r);
        }
        if (l > mx) {
            return _get(rs(x), mx + 1, rx, l, r);
        }

        return max(
            _get(ls(x), lx, mx, l, mx), 
            _get(rs(x), mx + 1, rx, mx + 1, r)
        );
    }

    ll get(int l, int r) {
        return _get(0, 0, n - 1, l, r);
    }

    void _update(int x, int lx, int rx, int l, int r, int addend) {
        if (r < lx || rx < l) {
            return;
        }
        
        if (l == lx && rx == r) {
            tree[x] += addend;
            lazy[x] += addend;
            return;
        }
        
        push(x);

        int mx = (lx + rx) >> 1;
        
        _update(ls(x), lx, mx, l, min(r, mx), addend);
        _update(rs(x), mx + 1, rx, max(l, mx + 1), r, addend);

        tree[x] = max(tree[ls(x)], tree[rs(x)]);
    }

    void update(int l, int r, int addend) {
        _update(0, 0, n - 1, l, r, addend);
    }
};

struct hld {
    int n;
    vt<vt<int> > g;
    vt<int> heavy_child, 
            subtree_size, 
            par, 
            path, 
            num, 
            path_size, 
            top, 
            depth;

    int all, cnt;
    seg_tree_push seg_tree;

    hld(vt<vt<int> > g) {
        this->n = g.size();
        this->all = 0;
        this->cnt = 1;
        this->g = g;
        this->heavy_child.resize(n, -1);
        this->subtree_size.resize(n);
        this->par.resize(n);
        this->path.resize(n);
        this->num.resize(n);
        this->path_size.resize(n);
        this->top.resize(n);
        this->depth.resize(n);
        this->seg_tree = seg_tree_push(n);
    };

    void dfs(int v, int pr) {
        par[v] = pr;
        subtree_size[v] = 1;
        for (int u : g[v]) {
            if (u == pr) continue;
            depth[u] = depth[v] + 1;
            dfs(u, v);
            subtree_size[v] += subtree_size[u];
            if (heavy_child[v] == -1 || subtree_size[u] > subtree_size[heavy_child[v]]) {
                heavy_child[v] = u;
            }
        }
    }

    void build_paths(int v, int pr) {
        path[v] = cnt - 1;
        num[v] = all++;
        if (path_size[cnt - 1] == 0) {
            top[cnt - 1] = v;
        }
        path_size[cnt - 1]++;
        if (heavy_child[v] != -1) {
            build_paths(heavy_child[v], v);
        }
        for (int u : g[v]) {
            if (u == pr || u == heavy_child[v]){
                continue;
            }
            cnt++;
            build_paths(u, v);
        }
    }

    ll ans_between_nodes(int node1, int node2) {
        ll res = 0;
        while (path[node1] != path[node2]) {
            if (depth[top[path[node1]]] < depth[top[path[node2]]]) {
                swap(node1, node2);
            }
            int start = top[path[node1]];
            res = max(res, seg_tree.get(num[start], num[node1]));
            node1 = par[start];
        }
        if (depth[node1] > depth[node2]) {
            swap(node1, node2);
        }
        res = max(res, seg_tree.get(num[node1], num[node2]));
        return res;
    }

    void modify(int node, int add){
        seg_tree.update(num[node], num[node], add);
    }
};

void solve() {
    int n; cin >> n;
    vt<vt<int> > g(n);
    For(i, n - 1) {
        int u, v; cin >> u >> v; u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    hld h = hld(g);
    h.dfs(0, -1);
    h.build_paths(0, -1);

    int m; cin >> m;
    For(i, m) {
        char op; cin >> op;
        int u, v; cin >> u >> v;
        if (op == 'I') {
            h.modify(u - 1, v);
        } else {
            cout << h.ans_between_nodes(u - 1, v - 1) << endl;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}