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

const int MAX = 1e9;
const int MOD = 1e9+7;
const ll  INF = 1e18;
const ld  PI  = 3.14159265358979323846;

struct seg_tree {
	int n;
	vt<int> tree;
	seg_tree(int n) {
		this->n = n;
		tree.resize(4 * n);
	}
    
    void _build(int x, int l, int r) {
		if (l == r) {
			tree[x] = 1;
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

	int _kth_order(int x, int lx, int rx, int k) {
        if (lx > rx) {
            return -1;
        }
		if (lx == rx) {
			return lx;
		}
		int mx = (lx + rx) >> 1;
        
        if (k <= tree[ls(x)]) {
            return _kth_order(ls(x), lx, mx, k);
        }
        if (k <= tree[x]) {
            return _kth_order(rs(x), mx + 1, rx, k - tree[ls(x)]);
        }
		return -1;
	}
 
	int kth_order(int k) { // indexed from 1
		return _kth_order(0, 0, n - 1, k);
	}
};
 
void solve() {
	int n; cin >> n;
	seg_tree tree = seg_tree(n);
	tree.build();
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solve();
	return 0;
}