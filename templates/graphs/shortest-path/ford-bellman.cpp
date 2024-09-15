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

struct ford_bellman {
	int n;
	vt<pair<pii, int> > edges;

	ford_bellman(int n, vt<pair<pii, int> > edges) {
		this->n = n;
		this->edges = edges;
	}

	vt<ll> find_negative_cycle() {
		vt<ll> dist(n, MAX);
		vt<int> par(n, -1);
		int start;
		for (int i = 0; i < n; ++i) {
			start = -1;
			for (auto & [e, c] : edges) {
				if (e.first == e.second && c < 0) {
					return vt<ll> {e.first};
				}

				if (dist[e.first] + c < dist[e.second]) {
					dist[e.second] = max(-INF, dist[e.first] + c);
					par[e.second] = e.first;
					start = e.second;
				}
			}
		}

		if (start == -1) {
			return vt<ll> {};
		}

		vt<ll> cycle;
		for (int v = start; ; v = par[v]) {
			if (v == start && cycle.size() > 1) break;
			cycle.push_back(v);
		}
		reverse(cycle.begin(), cycle.end());

		return cycle;
	}

	vt<ll> k_length_dist(int s, int k) {
		vt<vt<ll> > d(k + 1, vt<ll> (n, INF));
		d[0][s] = 0;
		for (int i = 1; i <= k; ++i) {
			for (auto & [e, c] : edges) {
				if (d[i - 1][e.first] + c < d[i][e.second]) {
					d[i][e.second] = d[i - 1][e.first] + c;
				}
			}
		}

		return d[k];
	}
};

void solve() {
	int n; cin >> n;
	vt<pair<pii, int> > edges;
	For(i, n) For(j, n) {
		int c; cin >> c;
		edges.push_back({{i, j}, c});
	}

	ford_bellman fb = ford_bellman(n, edges);
	vt<ll> cycle = fb.find_negative_cycle();
	if (cycle.size() == 0) {
		cout << "NO" << endl;
		return;
	}

	cout << "YES" << endl;
	cout << cycle.size() << endl;
	print(cycle);
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solve();
	return 0;
}