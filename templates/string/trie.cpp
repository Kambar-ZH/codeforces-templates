#include <bits/stdc++.h>

using namespace std;

#define For(i, n)           for(int i = 0; i < n; ++i)
#define all(x)              (x).begin(),(x).end()
#define rall(x)             (x).rbegin(),(x).rend()
#define ls(x)               x+x+1
#define rs(x)               x+x+2
// #define endl                '\n'

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

const int N = 1e6 + 10, K = 26;

struct vertex {
	vt<int> next;
    int count = 0;
};

struct trie {
	vertex t[N+1];
	int ver_count;

	trie() {
		t[0].next = vt<int> (K, -1);
		ver_count = 1;
	}
	
	void add_string(const string & s) {
		int v = 0;
		for (size_t i=0; i<s.length(); ++i) {
			char c = s[i]-'a';
			if (t[v].next[c] == -1) {
                t[ver_count].next = vt<int> (K, -1);
				t[v].next[c] = ver_count++;
			}
			v = t[v].next[c];
            t[v].count++;
		}
	}

    ll get_string(const string & s) {
		int v = 0;
        ll ans = 0;
		for (size_t i=0; i<s.length(); ++i) {
			char c = s[i]-'a';
			if (t[v].next[c] == -1) {
                break;
			}
			v = t[v].next[c];
            ans += t[v].count;
		}
        return ans;
	}
};

void solve() {
    int n; cin >> n;
    ll sum = 0;
	trie tr = trie();
    vt<string> a(n);
	For(i, n) {
        string s; cin >> s;
        a[i] = s;
        sum += s.length();
        reverse(all(s));
		tr.add_string(s);
	}

    ll ans = sum * n;

    For(i, n) {
        ans -= tr.get_string(a[i]);
    }
    cout << 2 * ans << endl;
}

// THE SOLUTION IS ALWAYS SIMPLE
// THE CODE IS ALWAYS SHORT

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef DEBUG
    freopen("output.txt", "w", stdout);
    freopen("input.txt", "r", stdin);
#endif
    int T = 1;
    For(t, T) solve();
    return 0;
}