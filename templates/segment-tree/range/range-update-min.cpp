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

struct SegTreePush {
	const int NO_PUSH = -MAX;

	int n;
	vt<int> lazy, tree;

	SegTreePush() {}

	SegTreePush(int n) {
		this->n = n;
		tree.resize(4 * n, MAX);
		lazy.resize(4 * n, NO_PUSH);
	}

	void push(int x, int lx, int rx) {
		if (lazy[x] == NO_PUSH) return;
		if (lx != rx) {
			lazy[ls(x)] = lazy[x];
			lazy[rs(x)] = lazy[x];
		}
		tree[x] = lazy[x];
		lazy[x] = NO_PUSH;
	}

	ll _get(int x, int lx, int rx, int l, int r) {
		push(x, lx, rx);

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

		return min(_get(ls(x), lx, mx, l, mx),
			_get(rs(x), mx + 1, rx, mx + 1, r));
	}

	ll get(int l, int r) {
		return _get(0, 0, n - 1, l, r);
	}

	void _update(int x, int lx, int rx, int l, int r, int value) {
		if (r < lx || rx < l) {
			return;
		}
		
		if (l == lx && rx == r) {
			lazy[x] = value;
			push(x, lx, rx);
			return;
		}
		
		push(x, lx, rx);

		int mx = (lx + rx) >> 1;
		
		_update(ls(x), lx, mx, l, min(r, mx), value);
		_update(rs(x), mx + 1, rx, max(l, mx + 1), r, value);

		tree[x] = min(tree[ls(x)], tree[rs(x)]);
	}

	void update(int l, int r, int value) {
		_update(0, 0, n - 1, l, r, value);
	}
};

void solve()
{
	int n; cin >> n;
	SegTreePush tree = SegTreePush(n);
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solve();
	return 0;
}