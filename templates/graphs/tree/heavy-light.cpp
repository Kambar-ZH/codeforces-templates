#include <bits/stdc++.h>

using namespace std;

#define For(i, n)           for(int i = 0; i < n; ++i)
#define qFor(i, x, n)       for(int i = x; i < n; ++i)
#define all(x)              (x).begin(),(x).end()
#define rall(x)             (x).rbegin(),(x).rend()

#define ld                  long double
#define pii                 pair<int, int>
#define vt                  vector
#define ll                  long long
#define endl                '\n'
#define ls					x + x + 1
#define rs					x + x + 2

// #define DEBUG
#ifdef DEBUG
#define dout(str)           do {cout << str;} while(false)
#else
#define dout(str)           do { } while ( false )
#endif

const int MAX = 1e9;
const int MOD = 1e9 + 7;
const ll  INF = 1e18;
const ld  PI  = 3.14159265358979323846;
 
template<typename T>
void read(vt<T> & a) {
    For(i, a.size()) cin >> a[i];
}
template<typename T>
void print(vt<T> & a) {
    For(i, a.size()) cout << a[i] << " ";
    cout << endl;
}
template<typename T>
void print2(vt<vt<T> > & a) {
    For(i, a.size()) {
        For(j, a[i].size()) cout << a[i][j] << " ";
        cout << endl;
    }
}
template<typename T>
void read2(vt<vt<T> > & a) {
    For(i, a.size()) For(j, a[i].size()) cin >> a[i][j];
}


// 100% good
struct seg_tree {
	int n;
	vt<int> a, max_tree;
	seg_tree(vt<int> _a) {
		n = _a.size(), a = _a;
		max_tree.resize(4 * n);
	}

    seg_tree() {}

	void _build(int x, int l, int r) {
		if (l == r) {
			max_tree[x] = a[l];
			return;
		}
		int m = (l + r) >> 1;
		_build(ls, l, m);
		_build(rs, m + 1, r);
		max_tree[x] = max(max_tree[ls], max_tree[rs]);
	}
 
	void build() {
		_build(0, 0, n - 1);
	}

	int _max_query(int x, int lx, int rx, int l, int r) {
		if (r < lx || rx < l) {
			return -MAX;
		}
		if (l <= lx && rx <= r) {
			return max_tree[x];
		}
		int mx = (lx + rx) >> 1;
		return max( _max_query(ls, lx, mx, l, r), 
                    _max_query(rs, mx + 1, rx, l, r) );
	}
 
	int max_query(int l, int r) {
		return _max_query(0, 0, n - 1, l, r);
	}

    void _set(int x, int lx, int rx, int l, int r, int v) {
        if (r < lx || rx < l) {
            return;
        }
        if (l <= lx && rx <= r) {
            max_tree[x] = v;
            return;
        }
        int mx = (lx + rx) >> 1;
        _set(ls, lx, mx, l, r, v);
        _set(rs, mx + 1, rx, l, r, v);
        max_tree[x] = max(max_tree[ls], max_tree[rs]);
    }

    void set_by_id(int id, int v) {
        _set(0, 0, n - 1, id, id, v);
    }
};

const int N = 1e5 + 5;
vt<int> pos(N, -1),    // position in segment tree
        cost,          // cost to go from pos[i] to pos[i + 1] 
        weight(N, 1),  // weight of the subtree
        height(N, 1),  // height of the node
        heavy(N, -1),  // pointer to the heavy child
        parent(N, -1), // pointer to upper heavy path
        head(N),       // pointer to top of the head of the heavy path
        edge_index(N); // index of the edge in cost array
vt<vt<int> > g(N);
map<pii, pii> mp; 
seg_tree tree;

void clear(int n) {
    cost.clear();
    mp.clear();
    For(i, n) {
        g[i].clear();
        pos[i] = heavy[i] = parent[i] = -1;
        height[i] = weight[i] = 1;
        head[i] = edge_index[i] = 0;
    }
}

// 100% good
void fix_metrics(int v, int p) {
    if (p != -1) {
        height[v] = height[p] + 1;
    }
    for (int to : g[v]) {
        if (to == p) continue;
        fix_metrics(to, v);
        if (heavy[v] == -1) {
            heavy[v] = to;
        } else if (weight[heavy[v]] < weight[to]) {
            heavy[v] = to;
        }
        weight[v] += weight[to];
    }
}

void find_parents(int v, int p) {
    for (int to : g[v]) {
        if (to == p) continue;
        if (heavy[v] != to) {
            parent[to] = v;
        }
        find_parents(to, v);
    }
}

// 80% good
void inorder_traverse(int v, int p, int h) {
    int id = cost.size();
    pos[v] = id;
    auto it = mp.find({v, p});
    if (it != mp.end()) {
        cost.push_back((*it).second.first);
        edge_index[(*it).second.second] = id;
        dout((*it).second.second << " " << id);
    } else {
        cost.push_back(0);
    }
    dout("traverse " << h << ": " << v + 1 << " " << p + 1 << " " << heavy[v] + 1 << " " << pos[v] << endl);
    head[v] = h;
    if (heavy[v] == -1) {
        return;
    }
    inorder_traverse(heavy[v], v, h);
}

// 80% good
int calc(int a, int b) {
    int mx = -MAX;
    for (; head[a] != head[b]; mx = max(mx, mp[{head[b], parent[head[b]]}].first), b = parent[head[b]]) {
        if (height[head[a]] > height[head[b]]) {
            swap(a, b);
        }
        dout("calc: " << a << " " << b << " " << height[a] << " " << height[b] << " " << tree.max_query(pos[head[b]] + 1, pos[b]) << endl);
        mx = max(mx, tree.max_query(pos[head[b]] + 1, pos[b]));
        dout("up: " << head[b] << " " << parent[head[b]] << endl);
    }
    if (height[a] > height[b]) {
        swap(a, b);
    }
    dout("pos: " << a + 1 << " " << b + 1 << " " << pos[a] << " " << pos[b] << endl);
    mx = max(mx, tree.max_query(pos[a] + 1, pos[b]));
    return mx;
}

int stupid(int v, int u, int p, vt<int> elems) {
    elems.push_back(v);
    if (v == u) {
        int mx = 0;
        for (int i = 0; i < elems.size() - 1; i++) {
            mx = max(mx, mp[{elems[i], elems[i + 1]}].first);
        }
        return mx;
    }
    for (int to : g[v]) {
        if (to == p) continue;
        int res = stupid(to, u, v, elems);
        if (res != 0) {
            return res;
        }
    }
    return 0;
}

// PROBLEM: https://www.spoj.com/problems/QTREE/

void solve()
{
    int n; cin >> n;
    vt<pii> edge;
    for (int i = 0; i < n - 1; i++) {
        int x, y, c; cin >> x >> y >> c; x--, y--;
        mp[{x, y}] = {c, i};
        mp[{y, x}] = {c, i};
        g[x].push_back(y);
        g[y].push_back(x);
        edge.push_back({x, y});
    }
    fix_metrics(0, -1);
    find_parents(0, -1);
    for (int i = 0; i < n; i++) {
        if (parent[i] != -1 || i == 0) {
            inorder_traverse(i, -1, i);
        }
    }
    dout(endl);
    tree = seg_tree(cost);
    tree.build();
    for (int i = 0; i < n; i++) {
        dout("cost: " << i << ": " << cost[i] << " " << tree.max_query(i, i) << endl);
    }
    for (;true;) {
        string op; cin >> op;
        if (op[0] == 'Q') {
            int v, u; cin >> v >> u; v--, u--;
            if (v == u) {
                cout << 0 << endl;
                continue;
            }
            int res = calc(v, u);
            // vt<int> elems;
            // if (res != stupid(v, u, -1, elems)) {
            //     cout << "FCK U" << v << " " << u << endl;
            //     return;
            // }
            cout << res << endl;
        } else if (op[0] == 'C') {
            int id, v; cin >> id >> v; id--;
            dout("change: " << edge_index[id] << " " << v);
            pii e = edge[id];
            mp[{e.first, e.second}] = {v, edge_index[id]};
            mp[{e.second, e.first}] = {v, edge_index[id]};
            tree.set_by_id(edge_index[id], v);
        } else {
            break;
        }
    }
    clear(n);
}
 
int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
// #define FILE
#ifdef FILE
    freopen("input.txt", "w", stdout);
    freopen("output.txt", "r", stdin);
#endif
    cout << setprecision(20) << fixed;
    int T = 1;
    cin >> T;
    For(t, T) {
        solve();
    }
    return 0;
}