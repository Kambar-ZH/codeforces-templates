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

namespace Diametr {
	void dfs(int u, int p, vt<int> & depth, vt<vt<int> > & g) {
		if (p != -1) depth[u] = depth[p] + 1;
		for (int v : g[u]) {
			if (v == p) continue;
			dfs(v, u, depth, g);
		}
	};

	int calc_diametr(vt<vt<int> > & g) {
		int n = g.size();
		vt<int> depth(n);
		dfs(0, -1, depth, g);
		int mx_depth_ver = 0;
		For(u, n) {
			if (depth[u] > depth[mx_depth_ver]) {
				mx_depth_ver = u;
			}
		}
		dfs(mx_depth_ver, -1, depth, g);
		return *max_element(all(depth));
	}
}

void solve() {
    
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}