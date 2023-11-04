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

pair<bool, vt<bool> > get_sign(vt<int> & a, int target) {
	int n = a.size();
	
	vt<int> first_half, second_half;
	
	for (int i = 0; i < n / 2; i++) {
		first_half.push_back(a[i]);
	}
	
	for (int i = n / 2; i < n; i++) {
		second_half.push_back(a[i]);
	}

	unordered_map<int, int> first_half_mp;
	for (int mask = 0; mask < (1 << first_half.size()); mask++) {
		int result = 0;
		for (int b = 0; b < first_half.size(); b++) {
			if (mask & (1 << b)) {
				result += first_half[b];
			} else {
				result -= first_half[b];
			}
		}
		first_half_mp[result] = mask;
	}

	unordered_map<int, int> second_half_mp;
	for (int mask = 0; mask < (1 << second_half.size()); mask++) {
		int result = 0;
		for (int b = 0; b < second_half.size(); b++) {
			if (mask & (1 << b)) {
				result += second_half[b];
			} else {
				result -= second_half[b];
			}
		}
		second_half_mp[result] = mask;
	}
	
	bool found = false;
	vt<bool> result;
	for (auto p : first_half_mp) {
		int need = target - p.first;
		if (second_half_mp.count(need)) {
			found = true;
			int mask_first = p.second;
			int mask_second = second_half_mp[need];
			for (int b = 0; b < first_half.size(); b++) {
				if (mask_first & (1 << b)) {
					result.push_back(true);
				} else {
					result.push_back(false);
				}
			}
			for (int b = 0; b < second_half.size(); b++) {
				if (mask_second & (1 << b)) {
					result.push_back(true);
				} else {
					result.push_back(false);
				}
			}
			break;
		} 
	}

	return {found, result};
}

void solve()
{
    int n, target; cin >> n >> target;
	vt<int> a(n); read(a);
	auto signs = get_sign(a, target); // 0 - negative, 1 - positive
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
    cin >> T;
    precalc();
    For(t, T) solve();
    return 0;
}