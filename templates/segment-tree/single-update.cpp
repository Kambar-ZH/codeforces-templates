#include <bits/stdc++.h>
 
using namespace std;
 
#define pb(i)               push_back(i)
#define For(i, n)           for(int i = 0; i < n; ++i)
#define qFor(i, x, n)       for(int i = x; i < n; ++i)
#define rFor(i, n)          for(int i = n - 1; i >= 0; --i)
#define see                 cout << endl;
#define all(x)              (x).begin(),(x).end()
#define rall(x)             (x).rbegin(),(x).rend()
 
#define ld                  long double
#define pii                 pair<int, int>
#define vt                  vector
#define ll                  long long
#define endl                '\n'
#define ls(x)               x+x+1
#define rs(x)               x+x+2
 

const int MOD = 1e9 + 7;
const int BINT = 32;
const int BLONG = 64;
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

struct node {
	ll value;
	node() {}
	node(ll value) : value(value) {};

	static node merge(node & n1, node & n2) {
		node r(n1.value + n2.value);
		return r;
	}

	static node identitity() {
		node r(0);
		return r;
	}
};

template<typename T>
struct seg_tree_single {
	int n;
	vt<T> a, tree;
	seg_tree_single(vt<T> a) {
		this->n = a.size(); 
		this->a = a;
		this->tree.resize(4 * n);
		this->build();
	}

	seg_tree_single(int n) {
		this->n = n; 
		this->tree.resize(4 * n, T::identitity());
	}

	void _build(int x, int l, int r) {
		if (l == r) {
			tree[x] = a[l];
			return;
		}

		int m = (l + r) >> 1;

		_build(ls(x), l, m);
		_build(rs(x), m + 1, r);
		
		tree[x] = T::merge(tree[ls(x)], tree[rs(x)]);
	}
 
	void build() {
		_build(0, 0, n - 1);
	}
 
	T _get(int x, int lx, int rx, int l, int r) {
		if (r < lx || rx < l) {
			return T::identitity();
		}
		
		if (l <= lx && rx <= r) {
			return tree[x];
		}

		int mx = (lx + rx) >> 1;
		
		T left_subtree = _get(ls(x), lx, mx, l, r);
		T right_subtree = _get(rs(x), mx + 1, rx, l, r);

		return T::merge(left_subtree, right_subtree);
	}
 
	T get(int l, int r) {
		return _get(0, 0, n - 1, l, r);
	}

	void _update(int x, int lx, int rx, int id, T v) {
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

		tree[x] = T::merge(tree[ls(x)], tree[rs(x)]);
	}

    void update(int id, T v) {
		_update(0, 0, n - 1, id, v);
	}
};
 
void solve()
{
	int n, m; cin >> n >> m;
	vt<node> a(n); 
	For(i, n) {
		cin >> a[i].value;
	}
	seg_tree_single<node> tree = seg_tree_single<node>(a);
	For(i, m) {
		int op; cin >> op;
		if (op == 1) {
			int id, v; cin >> id >> v;
			tree.update(id, node(v));
		} else {
			int l, r; cin >> l >> r; l--, r--;
			node n = tree.get(l, r);
			cout << n.value << endl;
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef DEBUG
	freopen("output.txt", "w", stdout);
	freopen("input.txt", "r", stdin);
#endif
	int T;
	T = 1;
	For(t, T) solve();
	return 0;
}