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

struct node {
	ll value;
	node() : value(0) {}
	node(ll value) : value(value) {}
};

template<typename N>
struct maxer {
	static N merge(N n1, N n2) {
		N r(max(n1.value, n2.value));
		return r;
	}
};

template<typename N, typename M>
struct seg_tree_single {
	int n;
	vt<N> a, tree;

	seg_tree_single() {}

	seg_tree_single(vt<N> a) {
		this->n = a.size(); 
		this->a = a;
		this->tree.resize(n << 2);
		this->build();
	}

	seg_tree_single(int n) {
		this->n = n; 
		this->tree.resize(n << 2);
	}

	void _build(int x, int l, int r) {
		if (l == r) {
			tree[x] = a[l];
			return;
		}

		int m = (l + r) >> 1;

		_build(ls(x), l, m);
		_build(rs(x), m + 1, r);
		
		tree[x] = M::merge(tree[ls(x)], tree[rs(x)]);
	}
 
	void build() {
		_build(0, 0, n - 1);
	}
 
	N _get(int x, int lx, int rx, int l, int r) {
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

		N lst = _get(ls(x), lx, mx, l, mx);
		N rst = _get(rs(x), mx + 1, rx, mx + 1, r);

		return M::merge(lst, rst);
	}
 
	N get(int l, int r) {
		return _get(0, 0, n - 1, l, r);
	}

	void _update(int x, int lx, int rx, int id, N & v) {
		if (id < lx || rx < id) {
			return;
		}

		if (lx == rx) {
            tree[x] = v;
			return;
		}

		int mx = (lx + rx) >> 1;

		_update(ls(x), lx, mx, id, v);
		_update(rs(x), mx + 1, rx, id, v);

		tree[x] = M::merge(tree[ls(x)], tree[rs(x)]);
	}

    void update(int id, N & v) {
		_update(0, 0, n - 1, id, v);
	}
};

template<typename N, typename M>
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
    seg_tree_single<N, M> seg_tree;

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
        this->seg_tree = seg_tree_single<N, M>(n);
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

    N ans_between_nodes(int u, int v) {
        N res = 0;
        while (path[u] != path[v]) {
            if (depth[top[path[u]]] < depth[top[path[v]]]) {
                swap(u, v);
            }
            int start = top[path[u]];
            res = M::merge(res, seg_tree.get(num[start], num[u]));
            u = par[start];
        }
        if (depth[u] > depth[v]) {
            swap(u, v);
        }
        return M::merge(res, seg_tree.get(num[u], num[v]));
    }

    N ans_between_edges(int u, int v) {
        N res = 0;
        while (path[u] != path[v]) {
            if (depth[top[path[u]]] < depth[top[path[v]]]) {
                swap(u, v);
            }
            int start = top[path[u]];
            res = M::merge(res, seg_tree.get(num[start], num[u]));
            u = par[start];
        }
        if (depth[u] > depth[v]) {
            swap(u, v);
        }
        if (u != v) {
            res = M::merge(res, seg_tree.get(num[u] + 1, num[v]));
        }
        return res;
    }

    void modify(int v, N val){
        seg_tree.update(num[v], val);
    }

    void modify_edge(pii edge, N val) {
        if (depth[edge.first] > depth[edge.second]) {
            modify(edge.first, val);
            return;
        }
        modify(edge.second, val);
    }
};

void solve() {
    int n; cin >> n;
    vt<vt<int> > g(n);
    vt<pair<pii, int> > edges;
    For(i, n - 1) {
        int u, v, c; cin >> u >> v >> c; u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
        edges.push_back({{u, v}, c});
    }
    hld<node, maxer<node>> h = hld<node, maxer<node>>(g);
    h.dfs(0, -1);
    h.build_paths(0, -1);
    For(i, n - 1) {
        h.modify_edge(edges[i].first, node(edges[i].second));
    }
    while (true) {
        string op; cin >> op;
        if (op == "CHANGE") {
            int id, x; cin >> id >> x;
            h.modify_edge(edges[id - 1].first, node(x));
        } else if (op == "QUERY") {
            int u, v; cin >> u >> v;
            ll ans = h.ans_between_edges(u - 1, v - 1).value;
            cout << ans << endl;
        } else {
            break;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}