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
#define um                  unordered_map

template<typename T> void read(vt<T> & a) {For(i, a.size()) cin >> a[i];}
template<typename T> void read2(vt<vt<T> > & a) {For(i, a.size()) read(a[i]);}
template<typename T> void print(vt<T> & a) {For(i, a.size()) cout << a[i] << " "; cout << endl;}
template<typename T> void print2(vt<vt<T> > & a) {For(i, a.size()) print(a[i]);}

const int MAX = 1e9;
const int MOD = 1000000007;
const ll  INF = 1e18;
const ld  PI  = 3.14159265358979323846;

struct modular {
private:
	int N = 1e6 + 1, MOD, MOD_POW, MOD_BASE;
	vt<ll> f, f_inv;

	void precalc_f() {
		f[0] = 1;
		for (int i = 1; i < f.size(); i++) {
			if (i % MOD_BASE) f[i] = f[i - 1] * i % MOD;
			else f[i] = f[i - 1];
		}
		for (int i = 0; i < f_inv.size(); i++) {
			f_inv[i] = inv_by_gcd(f[i]);
		}
	}

public:
	modular() {}

	modular(int MOD) {
		this->MOD_BASE = MOD;
		this->MOD_POW = 1;
		this->MOD = MOD;
		this->f = vt<ll> (min(N, MOD) + 1);
		this->f_inv = vt<ll> (min(N, MOD) + 1);
		this->precalc_f();
	};

	modular(int MOD_BASE, int MOD_POW) {
		this->MOD_BASE = MOD_BASE;
		this->MOD_POW = MOD_POW;
		this->MOD = bp_no_mod(MOD_BASE, MOD_POW);
		this->f = vt<ll> (min(N, MOD) + 1);
		this->f_inv = vt<ll> (min(N, MOD) + 1);
		this->precalc_f();
	};

	struct gcd_type { ll x, y, g; };

	static gcd_type ext_gcd(ll a, ll b) {
		if (b == 0) return {1, 0, a};
		gcd_type res = ext_gcd(b, a % b);
		return {res.y, res.x - a / b * res.y, res.g};
	}

	ll bp(ll a, ll b) {
		if (b == 0) return 1;
		if (b == 1) return a;
		if (b & 1) return a * bp(a, b - 1) % MOD;
		ll tmp = bp(a, b / 2);
		return tmp * tmp % MOD;    
	}

	// faster way to get inverse
	ll inv_by_gcd(ll n) {
		auto _gcd = ext_gcd(n, MOD);
		if (_gcd.g != 1) return -1;
		return (_gcd.x % MOD + MOD) % MOD;
	}
	
	ll inv(ll n) {
		return bp(n, (MOD - MOD / MOD_BASE) - 1);
	}

	ll F(ll n) {
		ll ans = 1;
		while (n > 1) {
			ans = ans * f[n % MOD] % MOD;
			ans = ans * bp(f[MOD], n / MOD) % MOD;
			n /= MOD_BASE;
		}
		return ans;
	}

	ll F_INV(ll n) {
		return inv_by_gcd(F(n));
	}

	ll exponent(ll n) {
		ll ans = 0;
		while (n) {
			n /= MOD_BASE;
			ans += n;
		}
		return ans;
	}

	ll C(int n, int k) {
		if (n < 0) return 0;
		if (k < 0) return 0;
		if (n - k < 0) return 0;
		return F(n) * F_INV(n - k) % MOD * F_INV(k) % MOD;
	}

	ll lucas(ll n, ll k) {
		if (n < k or k < 0) return 0;
		ll t = exponent(n) - exponent(k) - exponent(n - k);
		if (t >= MOD_POW) return 0;
		ll ans = F(n) * inv_by_gcd(F(k)) % MOD * inv_by_gcd(F(n - k)) % MOD;
		ans = ans * bp(MOD_BASE, t) % MOD;
		return ans;
	}

	// be carefull with overflow
	static ll bp_no_mod(ll a, int b) {
		if (b == 0) return 1;
		if (b == 1) return a;
		if (b & 1) return a * bp_no_mod(a, b - 1);
		ll tmp = bp_no_mod(a, b / 2);
		return tmp * tmp;
	}

	static ll lcm(ll a, ll b) {
		return a / __gcd(a, b) * b;
	}

	static ll CRT(vt<ll> rems, vt<ll> mods) {
		auto normalize = [&] (ll x, ll mods) { 
			x %= mods; 
			if (x < 0) x += mods; 
			return x;
		};
		for(int i = 0; i < rems.size(); i++) rems[i] = normalize(rems[i], mods[i]);
		ll ans = rems[0], _lcm = mods[0];
		for(int i = 1; i < rems.size(); i++) {
			auto _gcd = ext_gcd(_lcm, mods[i]);
			ll x1 = _gcd.x;
			ll g = _gcd.g;
			if ((rems[i] - ans) % g != 0) {
				// return cerr << "No solutions" << endl, 0;
				return -1;
			}
			ans = normalize(ans + x1 * (rems[i] - ans) / g % (mods[i] / g) * _lcm, _lcm * mods[i] / g);
			_lcm = lcm(_lcm, mods[i]);
		}
		return ans;
	}

	static um<int, int> factors_occurence_cnt(int n) {
		um<int, int> primes;
		for (int d = 2; d * d <= n; d++) {
			if (n % d != 0) continue;
			while (n % d == 0) {
				n /= d;
				primes[d]++;
			}
		}
		if (n != 1) {
			primes[n]++;
		}
		return primes;
	}

	static ll lucas(ll n, ll k, int mod) {
		um<int, int> mp = modular::factors_occurence_cnt(mod);
		vt<ll> rems, mods;
		for (auto & [key, val] : mp) {
			modular math = modular(key, val);
			mods.push_back(bp_no_mod(key, val));
			rems.push_back(math.lucas(n, k));
		}
		return CRT(rems, mods);
	}

	static ll lucas_up_to(ll n, ll k, ll up_to, int mod) {
		return lucas((up_to - n % up_to) % up_to + k - 1, k - 1, mod);
	}

	// a * x = b mod m
	static vt<ll> congruence(ll a, ll b, ll m) {
		vt<ll> res;
		ll g = __gcd(a, m);
		if (b % g != 0) return res;
		// a / g * x + m / g * k = b / g
		ll x = ext_gcd(a / g, m / g).x * (b / g);
		ll step = m / g;
		for (int k = 0; k < m; k += step) {
			res.push_back((x + k) % m);
		}
		return res;
	}
};

void solve() {
	ll n, up_to, mod; cin >> n >> up_to >> mod;
	ll k = (n + up_to - 1) / up_to;
	ll res = modular::lucas_up_to(n, k, up_to, mod);
	cout << k << " " << res << endl;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int T = 1;
	For(t, T) solve();
	return 0;
}