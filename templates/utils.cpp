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

template<typename T>
vt<T> unique(vt<T> vec) {
    unordered_set<T> s;
    for (T i : vec)
        s.insert(i);
    vec.assign( s.begin(), s.end() );
    sort( vec.begin(), vec.end() );
    return vec;
} 

void solve()
{
    int n; cin >> n;
    vt<ll> a(n); read(a);
    vt<ll> res = unique(a);
    print(res);
}

void precalc() {}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef DEBUG
    freopen("output.txt", "w", stdout);
    freopen("input.txt", "r", stdin);
#endif
    srand( time(NULL) );
    int T;
    T = 1;
    precalc();
    For(t, T) solve();
    return 0;
}