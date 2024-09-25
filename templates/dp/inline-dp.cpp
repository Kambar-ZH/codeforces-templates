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
const int MOD = 998244353;
const ll  INF = 1e18;
const ld  PI  = 3.14159265358979323846;

// https://atcoder.jp/contests/abc372/tasks/abc372_f

void solve()
{
	ll n, m, k; cin >> n >> m >> k;
	deque<ll> dp;
	deque<ll> tmp;
	for (ll i = 0;i<n;i++) {
		dp.push_back(1);
		tmp.push_back(1);
	}
	vector<pair<ll,ll>> ed;
	for (ll i = 0;i<m;i++) {
		ll u, v; cin >> u >> v; u--; v--;
		ed.push_back({u,v});
	}
	for (ll i = 0;i<k;i++) {
		dp.push_back(dp.front());
		dp.pop_front();
		for (pair<ll,ll> u : ed) {
			dp[u.first] += tmp[u.second];
			dp[u.first] %= MOD;
		}
		tmp.push_back(tmp.front());
		tmp.pop_front();
		for (pair<ll,ll> u : ed) {
			tmp[u.first] = dp[u.first];
		}
	}
	cout << dp[0] << endl;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solve();
	return 0;
}