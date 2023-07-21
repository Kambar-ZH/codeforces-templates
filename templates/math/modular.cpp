#include <bits/stdc++.h>

using namespace std;

#define ll                  long long
#define vt                  vector
#define For(i, n)           for(int i = 0; i < n; ++i)
#define pii                 pair<int, int>

const int MOD = 1e9 + 7;

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

ll mod_plus(ll a, ll b) {return (a + b) % MOD;}
ll mod_minus(ll a, ll b) {return (a - b + MOD) % MOD;}
ll mod_mult(ll a, ll b) {return a * b % MOD;}
ll mod_div(ll a, ll b) {return a * inv(b) % MOD;}

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
    int n, k; cin >> n >> k;
    cout << C(n, k) << endl;
}

int main()
{
    precalc_f();
    return 0;
}