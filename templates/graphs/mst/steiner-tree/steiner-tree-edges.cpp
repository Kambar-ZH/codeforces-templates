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

vt<vt<ll> > steiner_tree(vt<vt<pii> > & g, vt<int> terminals) {
	int n = g.size();
	int k = terminals.size();
	vt dp(1 << k, vt<ll>(n, INF));
	for (int i = 0; i < k; i++) dp[1 << i][terminals[i]] = 0;
	for (int mask = 1; mask < (1 << k); mask++) {
		for (int sub = mask; sub > 0; sub = (sub - 1) & mask) {
			for (int i = 0; i < n; i++) {
				dp[mask][i] = min(dp[mask][i], dp[sub][i] + dp[mask - sub][i]);
			}
		}
		priority_queue<pair<ll, int>, vt<pair<ll, int>>, greater<>> pq;
		for (int i = 0; i < n; i++) pq.emplace(dp[mask][i], i);
		while (!pq.empty()) {
			auto [d, u] = pq.top();
			pq.pop();
			if (d > dp[mask][u]) continue;
			for (auto [v, l]: g[u]) {
				if (dp[mask][v] > d + l) {
					dp[mask][v] = d + l;
					pq.emplace(d + l, v);
				}
			}
		}
	}
	return dp;
}

// https://atcoder.jp/contests/abc364/tasks/abc364_g

void solve() {
	int n, m, k;
	cin >> n >> m >> k;
	--k;
	vt<vt<pii>> g(n);
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		--a, --b;
		g[a].emplace_back(b, c);
		g[b].emplace_back(a, c);
	}
	vt<int> terminals(k); iota(all(terminals), 0);
	auto dp = steiner_tree(g, terminals);
	for (int i = k; i < n; i++) {
		cout << dp.back()[i] << endl;
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solve();
	return 0;
}