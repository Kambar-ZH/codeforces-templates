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

struct Edge
{
	int from, to, cap, flow;
	Edge(int _from, int _to, int _cap, int _flow) {
		from = _from;
		to = _to;
		cap = _cap;
		flow = _flow;
	}
};


// 1.1 dfs - find any path from start to finish
// 1.2 dfs - get delta => min(flow[v]) over all v on path
// 1.3 dfs - substract delta from edges on path and build reverse edges
// 1.4 dfs - build new graph 
// 1.5 repeat steps until 1.1 is not halt
// 1.6 return overall delta summation

int n, m;

int dfs(int v, int delta, vt<bool> & used, vt<vt<Edge> > & g, vt<Edge> & gr) {
	used[v] = true;
	if (v == n - 1) {
		return delta;
	}
	int min_delta = MAX; 
	vt<Edge> gv;
	for (auto& e : g[v]) {
		if (used[e.to]) continue;
		min_delta = dfs(e.to, min(delta, e.cap - e.flow), used, g, gr);
		if (min_delta != MAX) {
			e.flow += min_delta;
			gr.push_back(Edge(e.to, v, e.cap, e.cap - e.flow));
			break;
		}
	}
	return min_delta;
}

vt<vt<Edge> > build(vt<vt<Edge> > g, vt<Edge> gr) {
	vt<vt<Edge> > gnew(n);
	for (int i = 0; i < n; i++) {
		for (auto& e : g[i]) {
			if (e.flow == e.cap) continue; 
			gnew[i].push_back(e);
		}
	}
	g = gnew;
	for (auto& rev : gr) {
		bool found = false;
		for (auto& e : g[rev.from]) {
			if (e.to == rev.to && e.cap == rev.cap) {
				e.flow = rev.flow;
				assert(found == false);
				found = true;
			}
		}
		if (!found) {
			g[rev.from].push_back(Edge(rev.from, rev.to, rev.cap, rev.flow));
		}
	}
	return g;
}

void solve()
{
	cin >> n >> m;
	vt<vt<Edge> > g(n);
	For(i, m) {
		int f, t, c; cin >> f >> t >> c; f--, t--;
		g[f].push_back(Edge(f, t, c, 0));
	}
	int ans = 0;
	while (true) {
		vt<bool> used(n);
		vt<Edge> gr;
		int delta = dfs(0, MAX, used, g, gr);
		if (delta == MAX) {
			break;
		} 
		// assert(delta > 0);
		ans += delta;
		g = build(g, gr);
	}
	cout << ans << endl;
}

int main()
{
		ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef DEBUG
		freopen("output.txt", "w", stdout);
		freopen("input.txt", "r", stdin);
#endif
		int T = 1;
		cin >> T;
		For(t, T) {
				solve();
		}
		return 0;
}