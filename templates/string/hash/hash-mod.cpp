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

struct hashed_string {
    const int MOD = 1000003579;

	int n;
	string s;
	vt<ll> hash;
	vt<ll> power;
	int alph;

	hashed_string(string s) {
		this->s = s;
		this->n = s.size();
		this->hash = vt<ll> (n + 1);
		this->power = vt<ll> (n + 1);
		this->alph = 53;

		this->precalc();
	}

	void precalc() {
		power[0] = 1;
		for (int i = 0; i < n; i++) {
			hash[i + 1] = (hash[i] + (s[i] - 'a' + 1) * power[i] % MOD) % MOD;
			power[i + 1] = (power[i] * alph) % MOD;
		}
	}

	// hash_on_range - 0-indexed, range inclusive
	ll hash_on_range(int l, int r) {
		return (hash[r + 1] - hash[l] + MOD) * power[n - l] % MOD;
	}
};

void solve()
{
	string s; cin >> s;
	hashed_string hs(s);
	int m; cin >> m;
	for (int i = 0; i < m; i++) {
		int l1, r1, l2, r2; cin >> l1 >> r1 >> l2 >> r2;
		l1--, r1--, l2--, r2--;
		ll hash1 = hs.hash_on_range(l1, r1); 
		ll hash2 = hs.hash_on_range(l2, r2); 
		cout << (hash1 == hash2 ? "Yes" : "No") << endl;
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solve();
	return 0;
}