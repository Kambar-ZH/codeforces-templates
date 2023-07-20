#include <bits/stdc++.h>

using namespace std;

#define For(i, n)           for(int i = 0; i < n; ++i)
#define qFor(i, x, n)       for(int i = x; i < n; ++i)
#define all(x)              (x).begin(),(x).end()
#define rall(x)             (x).rbegin(),(x).rend()

#define ld                  long double
#define pii                 pair<int, int>
#define vt                  vector
#define ll                  long long
// #define endl                '\n'

#define DEBUG
#ifdef DEBUG
#define dout(str)           do {cout << str;} while(false)
#else
#define dout(str)           do { } while ( false )
#endif

const int MAX = 1e9;
const int MOD = 1e9 + 7;
const ll  INF = 1e18;
const ld  PI  = 3.14159265358979323846;
 
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

const int N = 1e5 + 5;
const int L = 20;
vt<vt<int> > que(N, vt<int> (L + 1));
vt<int> pow2(L);

void precalc(vt<int> & a) {
    int c2 = 1;
    for (int i = 0; i < L; i++) {
        pow2[i] = c2;
        c2 *= 2;
    }
    int n = a.size();
    for (int i = 0; i < n; i++) {
        que[i][0] = a[i];
    }
    for (int l = 1; l < L; l++) {
        for (int i = 0; i < n; i++) {
            if (i + (pow2[l - 1]) < n) {
                que[i][l] = min(que[i + (pow2[l - 1])][l - 1], que[i][l - 1]);
            } else {
                que[i][l] = que[i][l - 1];
            }
        }
    }
} 

int clz(int N) {
    return N ? 31 - __builtin_clz(N) : -MAX;
}

int ask(int l, int r) {
    if (l > r) swap(l, r);
    if (l == r) {
        return que[l][0];
    }
    int dif = r - l;
    int p2 = clz(dif);
    int mn = min(que[l][p2], que[r - (1 << p2) + 1][p2]);
    return mn;
}

void solve()
{
    int n, m; cin >> n >> m;
    vt<int> a(n); cin >> a[0];
    for (int i = 1; i < n; i++) {
        a[i] = (a[i - 1] * 23 + 21563) % 16714589;
    }
    precalc(a);
    vt<pii> q(2); cin >> q[0].first >> q[0].second;
    int res = -1;
    for (int i = 0; i < m; i++) {
        res = ask(q[0].first - 1, q[0].second - 1);
        q[1].first = (17 * q[0].first + 751 + res + 2 * (i + 1)) % n + 1;
        q[1].second = (13 * q[0].second + 593 + res + 5 * (i + 1)) % n + 1;
        swap(q[0], q[1]);
    }
    cout << q[1].first << " " << q[1].second << " " << res << endl;
}
 
int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
// #define FILE
#ifdef FILE
    freopen("output.txt", "w", stdout);
    freopen("input.txt", "r", stdin);
#endif
    cout << setprecision(20) << fixed;
    int T = 1;
    // cin >> T;
    For(t, T) {
        solve();
    }
    return 0;
}