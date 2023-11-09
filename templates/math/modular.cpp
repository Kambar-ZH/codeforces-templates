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

ll mod_plus(ll a, ll b) {return (a + b) % MOD;}
ll mod_minus(ll a, ll b) {return (a - b + MOD) % MOD;}
ll mod_mult(ll a, ll b) {return a * b % MOD;}
ll mod_div(ll a, ll b) {return a * inv(b) % MOD;}

ll bp(ll a, ll b) {
    if (b == 0) return 1;
    if (b == 1) return a;
    if (b & 1) return a * bp(a, b - 1) % MOD;
    ll tmp = bp(a, b / 2);
    return tmp * tmp % MOD;    
}

ll inv(ll n) {
    return bp(n, MOD - 2);
}

const int N = 2e5;
vt<ll> F(N, 1), F_INV(N, 1);

void precalc_f() {
    for (int i = 1; i < N; i++) {
        F[i] = (F[i - 1] * i) % MOD;
    }
    for (int i = 1; i < N; i++) {
        F_INV[i] = inv(F[i]) % MOD;
    }
}

ll C(int n, int k) {
    if (n < 0) return 0;
    if (k < 0) return 0;
    if (n - k < 0) return 0;
    return F[n] * F_INV[n - k] % MOD * F_INV[k] % MOD;
}

void solve() {
    
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}