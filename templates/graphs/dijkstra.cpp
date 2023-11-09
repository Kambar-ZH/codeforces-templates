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

vt<ll> dijkstra(int s, vt<vt<pii> > g) {
	int n = g.size();
	vt<ll> d(n, INF), p(n);
	d[s] = 0;
	priority_queue<pair<ll, int> > q;
	q.push(make_pair(0, s));
	while (!q.empty()) {
		int v = q.top().second;
		ll cur_d = -q.top().first;
		q.pop();
        
		if (cur_d > d[v])  continue;
 
		for (int j = 0; j < g[v].size(); ++j) {
			int to = g[v][j].first,
				len = g[v][j].second;
			if (d[v] + len < d[to]) {
				d[to] = d[v] + len;
				p[to] = v;
				q.push(make_pair(-d[to], to));
			}
		}
	}
	return d;
}

void solve() {
    int n, m; cin >> n >> m;
	int s, f; cin >> s >> f; s--, f--;
	vt<vt<pii> > g(n); 
	For(i, m) {
		int u, v, d; cin >> u >> v >> d; u--, v--;	
		g[u].push_back({v, d});
		g[v].push_back({u, d});
	}
    vt<ll> dist_s = dijkstra(s, g);
    cout << "dist from s: [" << s << "]" << "to f: [" << f << "] = " << dist_s[f] << endl;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solve();
	return 0;
}