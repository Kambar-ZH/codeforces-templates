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

struct eratosphen {
    int N;
    vt<bool> is_prime;
    vt<int> largest_prime;
    vt<int> primes;
    eratosphen(int N) {
        this->N = N;
        this->is_prime = vt<bool> (N, true);
        this->largest_prime = vt<int> (N); iota(all(largest_prime), 0);
        this->sieve();
    }

    void sieve() {
        is_prime[0] = is_prime[1] = false;
        for (int i = 2; i * i < N; i++) {
            if (is_prime[i]) {
                primes.push_back(i);
                for (int j = i * i; j < N; j += i) {
                    is_prime[j] = false;
                    largest_prime[j] = i;
                }
            }
        }
    }

    // not including 1
    vt<int> factorize(int n) {
        vt<int> primes;
        while (largest_prime[n] != 1) {
            primes.push_back(largest_prime[n]);
            n = n / largest_prime[n];
        }
        return primes;
    }

    // not including 1
    map<int, int> map_factorize(int n) {
        map<int, int> primes;
        while (largest_prime[n] != 1) {
            primes[largest_prime[n]] += 1;
            n = n / largest_prime[n];
        }
        return primes;
    }
};

vt<int> factorize(int n) {
    vt<int> primes;
    for (int d = 2; d * d <= n; d++) {
        if (n % d == 0) {
            while (n % d == 0) {
                n /= d;
                primes.push_back(d);
            }
        }
    }
    if (n != 1) {
        primes.push_back(n);
    }
    return primes;
}

vt<int> get_divisors(int n) {
    vt<int> divs;
    for (int d = 2; d * d <= n; d++) {
        if (n % d == 0) {
            divs.push_back(d);
            if (d * d != n) {
                divs.push_back(n / d);
            }
        }
    }
    return divs;
}

void solve() {
    int n; cin >> n;
    eratosphen seive = eratosphen(n + 1);
    vt<int> d1 = factorize(n), d2 = seive.factorize(n);
    print(d1);
    print(d2);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}