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

struct EulerDetour {
	vt<int> sz, tin, tout, ver;
	vt<int> par, val;
	vt<vt<pii> > *g;
	
	EulerDetour(
		int n,
		vt<vt<pii> > *g
	) {
		this->g = g;
		this->sz.resize(n);
		this->tin.resize(n);
		this->tout.resize(n);
		this->par = vt<int> (n, -1);
		this->val.resize(n);
		this->precalc();
	}

	void _precalc(int u, int p) {
		sz[u] = 1;
		ver.push_back(u);
		tin[u] = ver.size() - 1;
		for (auto [v, c] : (*g)[u]) {
			if (v == p) continue;
			_precalc(v, u);
			sz[u] += sz[v];
			par[v] = u;
			val[v] = c;
		}
		tout[u] = ver.size() - 1;
	}

	void precalc() {
		_precalc(0, -1);
	}
};

void solve() {
	
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solve();
	return 0;
}