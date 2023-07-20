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
 
 
const int MAX = 1e9;
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
 
struct seg_tree {
	int n;
	vt<int> a, tree;
	seg_tree(vt<int> _a) {
		n = _a.size(), a = _a;
		tree.resize(4 * n);
	}
 
	void _build(int x, int l, int r) {
		if (l == r) {
			tree[x] = a[l];
			return;
		}
		int m = (l + r) >> 1;
		_build(ls(x), l, m);
		_build(rs(x), m + 1, r);
		tree[x] = tree[ls(x)] + tree[rs(x)];
	}
 
	void build() {
		_build(0, 0, n - 1);
	}
 
	int _min_query(int x, int lx, int rx, int l, int r) {
		if (r < lx || rx < l) {
			return MAX;
		}
		if (l <= lx && rx <= r) {
			return tree[x];
		}
		int mx = (lx + rx) >> 1;
		int left_subtree = _min_query(ls(x), lx, mx, l, r);
		int right_subtree = _min_query(rs(x), mx + 1, rx, l, r);
		return left_subtree + right_subtree;
	}
 
	int min_query(int l, int r) {
		return _min_query(0, 0, n - 1, l, r);
	}

	void _update(int x, int lx, int rx, int l, int r, int v) {
		if (r < lx || rx < l) {
			return;
		}
		if (l <= lx && rx <= r) {
            tree[x] = v;
			return;
		}
		int mx = (lx + rx) >> 1;
		_update(ls(x), lx, mx, l, r, v);
		_update(rs(x), mx + 1, rx, l, r, v);
		tree[x] = tree[ls(x)] + tree[rs(x)];
	}

    void update(int l, int v) {
		_update(0, 0, n - 1, l, l, v);
	}
};
 
void solve()
{
	int n; cin >> n;
	vt<int> a(n); read(a);
	seg_tree tree = seg_tree(a);
	tree.build();
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