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

namespace TopSort {
	void dfs(int v, vt<bool> & visited, vt<int> & post_order, vt<vt<int> > & g) {
		visited[v] = true;
		for (int u : g[v]) {
			if (visited[u]) continue;
			dfs(u, visited, post_order, g);
		}
		post_order.push_back(v);
	}

	vt<int> top_sort(vt<vt<int> > & g) {
        int n = g.size();
		vt<int> post_order;
		vt<bool> visited(n);
		for (int v = 0; v < n; v++) {
			if (visited[v]) continue; 
			dfs(v, visited, post_order, g);
		}
        reverse(all(post_order));
        return post_order;
	}
}

void solve() {
    
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}