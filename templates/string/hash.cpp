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

#define sim template < class c
#define ris return * this
#define dor > debug & operator <<
#define eni(x) sim > typename \
enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge { c b, e; };
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0);
sim > char dud(...);
#define LOCAL
struct debug {
#ifdef LOCAL
~debug() { cerr << endl; }
eni(!=) cerr << boolalpha << i; ris; }
eni(==) ris << range(begin(i), end(i)); }
sim, class b dor(pair < b, c > d) {
ris << "(" << d.first << ", " << d.second << ")";
}
sim dor(rge<c> d) {
*this << "[";
for (auto it = d.b; it != d.e; ++it)
	*this << ", " + 2 * (it == d.b) << *it;
ris << "]";
}
#else
sim dor(const c&) { ris; }
#endif
};
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "

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

const int MAX = 1e9;
const int MOD = 1e9+7;
const int BINT = 32;
const int BLONG = 64;
const ll  INF = 1e18;
const ld  PI  = 3.14159265358979323846;

// THE SOLUTION IS ALWAYS SIMPLE
// THE CODE IS ALWAYS SHORT

struct hashed_string {
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
		this->alph = 31;

		this->precalc();
	}

	void precalc() {
		power[0] = 1;
		for (int i = 0; i < n; i++) {
			hash[i + 1] = hash[i] + (s[i] - 'a' + 1) * power[i];
			power[i + 1] = (power[i] * alph);
		}
	}

	// hash_on_range - 0-indexed, range inclusive
	ll hash_on_range(int l, int r) {
		return (hash[r + 1] - hash[l]) * power[n - l];
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

void precalc() {}

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef DEBUG
	freopen("output.txt", "w", stdout);
	freopen("input.txt", "r", stdin);
#endif
	int T;
	T = 1;
	precalc();
	For(t, T) solve();
	return 0;
}