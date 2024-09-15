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

struct Node {
	ll value;
	Node() : value(0) {}
	Node(ll value) : value(value) {}
};

template<typename N>
struct Summer {
	static N merge(N & n1, N & n2) {
		N r(n1.value + n2.value);
		return r;
	}
};

template<typename N, typename M>
struct SegTreeSingle {
	int n;
	vt<N> a, tree;

	SegTreeSingle() {}

	SegTreeSingle(vt<N> a) {
		this->n = a.size(); 
		this->a = a;
		this->tree.resize(n << 2);
		this->build();
	}

	SegTreeSingle(int n) {
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

	void update(int id, N v) {
		_update(0, 0, n - 1, id, v);
	}
};
 
void solve()
{
	int n, m; cin >> n >> m;
	vt<Node> a(n); 
	For(i, n) {
		cin >> a[i].value;
	}
	auto tree = SegTreeSingle<Node, Summer<Node>>(a);
	For(i, m) {
		int op; cin >> op;
		if (op == 1) {
			int id, v; cin >> id >> v; id--;
			Node n = Node(v);
			tree.update(id, n);
		} else {
			int l, r; cin >> l >> r; l--, r--;
			Node n = tree.get(l, r);
			cout << n.value << endl;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solve();
	return 0;
}