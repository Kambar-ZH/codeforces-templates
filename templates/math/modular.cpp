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

struct Mint {
	ll x;
	Mint():x(0){}
	Mint(ll x):x((x%MOD+MOD)%MOD){}
	Mint& fix() { x = (x%MOD+MOD)%MOD; return *this;}
	Mint operator-() const { return Mint(0) - *this;}
	Mint operator~() const { return Mint(1) / *this;}
	Mint& operator+=(const Mint& a){ if((x+=a.x)>=MOD) x-=MOD; return *this;}
	Mint& operator-=(const Mint& a){ if((x+=MOD-a.x)>=MOD) x-=MOD; return *this;}
	Mint& operator*=(const Mint& a){ (x*=a.x)%=MOD; return *this;}
	Mint& operator/=(const Mint& a){ (x*=a.ex(MOD-2).x)%=MOD; return *this;}
	Mint& operator&=(const Mint& a){ x &= 1; return *this;}
	Mint operator+(const Mint& a)const{ return Mint(*this) += a;}
	Mint operator-(const Mint& a)const{ return Mint(*this) -= a;}
	Mint operator*(const Mint& a)const{ return Mint(*this) *= a;}
	Mint operator/(const Mint& a)const{ return Mint(*this) /= a;}
	Mint operator&(const Mint& a)const{ return Mint(*this) &= a;}
	Mint ex(ll t) const {
		if(!t) return 1;
		Mint res = ex(t/2);
		res *= res;
		return (t&1)?res*x:res;
	}
	bool operator<(const Mint& a)const{ return x < a.x;}
	bool operator==(const Mint& a)const{ return x == a.x;}

	Mint ex(Mint x, ll t) { return x.ex(t);}
};

istream& operator>>(istream&i,Mint&a){i>>a.x;return i;}
ostream& operator<<(ostream&o,const Mint&a){o<<a.x % MOD;return o;}

struct Math {
	int N;
	vt<Mint> f, f_inv;

	Math() {}

	Math(int N) {
		this->N = N+1;
		precalc_f();
	}

	void precalc_f() {
		f = vt<Mint> (N), f_inv = vt<Mint> (N);
		f[0] = 1, f[1] = 1;
		for (int i = 2; i < f.size(); i++) f[i] = f[i - 1] * i;
		for (int i = 0; i < f_inv.size(); i++) f_inv[i] = inv(f[i]);
	}

	Mint bp(Mint a, int b) {
		if (b == 0) return 1;
		if (b == 1) return a;
		if (b & 1) return a * bp(a, b - 1);
		Mint tmp = bp(a, b / 2);
		return tmp * tmp;
	}

	Mint inv(Mint n) {
		return bp(n, MOD - 2);
	}

	Mint F(int n) {
		assert(0 <= n && n < f.size());
		return f[n];
	}

	Mint F_INV(int n) {
		assert(0 <= n && n < f_inv.size());
		return f_inv[n];
	}

	Mint C(int n, int k) {
		if (n < 0) return 0;
		if (k < 0) return 0;
		if (n - k < 0) return 0;
		return F(n) * F_INV(n - k) * F_INV(k);
	}

	Mint stars_and_bars(int n, int k) {
		return C(n + k - 1, k - 1);
	}

	Mint lucas(int n, int k) {
		if (k < 0 || k > n) return 0;
		if (k == 0 || k == n) return 1;
		if (n < MOD) return C(n, k);
		return (lucas(n / MOD, k / MOD) * lucas(n % MOD, k % MOD));
	}
};

static Math math = Math(2e5);

struct gcd_type { ll x, y, g; };
gcd_type ext_gcd(ll a, ll b) {
	if (b == 0) return {1, 0, a};
	gcd_type res = ext_gcd(b, a % b);
	return {res.y, res.x - a / b * res.y, res.g};
}

ll lcm(ll a, ll b) {
	return a / __gcd(a, b) * b;
}

// CRT - mods are not necessarily coprime
ll CRT(vt<ll> rem, vt<ll> mod) {
	auto normalize = [&] (ll x, ll mod) { 
		x %= mod; 
		if (x < 0) x += mod; 
		return x;
	};
	for (int i = 0; i < rem.size(); i++) {
		rem[i] = normalize(rem[i], mod[i]);
	}
	ll ans = rem[0], _lcm = mod[0];
	for (int i = 1; i < rem.size(); i++) {
		auto _gcd = ext_gcd(_lcm, mod[i]);
		int x1 = _gcd.x;
		int g = _gcd.g;
		if ((rem[i] - ans) % g != 0) {
			return cerr << "No solutions" << endl, 0;
		}
		ans = normalize(
			ans + x1 * (rem[i] - ans) / g % (mod[i] / g) * _lcm, 
			_lcm * mod[i] / g
		);
		_lcm = lcm(_lcm, mod[i]);
	}
	return ans;
}

void solve() {
	
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solve();
	return 0;
}