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

template<typename T> void read(vt<T> & a) {For(i, a.size()) cin >> a[i];}
template<typename T> void read2(vt<vt<T> > & a) {For(i, a.size()) read(a[i]);}
template<typename T> void print(vt<T> & a) {For(i, a.size()) cout << a[i] << " "; cout << endl;}
template<typename T> void print2(vt<vt<T> > & a) {For(i, a.size()) print(a[i]);}

const int MAX = 1e9;
const int MOD = 1000000007;
const ll  INF = 1e18;
const ld  PI  = 3.14159265358979323846;

struct Line {
	ll k, c;
	
	Line() {}
	Line(ll k, ll c) : k(k), c(c) {}

	ll Y(ll x) {return k * x + c;}
};

struct Maxer {
	static ll zero_value() {return -INF;}
	static ll merge(ll ls, ll rs) {return max(ls, rs);}
	static bool need_swap(ll a, ll b) {return a > b;}
};

struct Miner {
	static ll zero_value() {return INF;}
	static ll merge(ll ls, ll rs) {return min(ls, rs);}
	static bool need_swap(ll a, ll b) {return a < b;}
};

struct Node {
	Line line;
	Node *left = nullptr, *right = nullptr;

	Node(Line line) : line(line) {}
};

template<typename T>
struct LiChaoTree {
	int L, R;
	Node *root = nullptr;

	LiChaoTree() {
		L = 0, R = MAX, root = new Node(Line(0, T::zero_value()));
	}

	void _add_segment(Node *node, int l, int r, int L, int R, Line new_line) {
		if (l > r || r < L || R < l) {
			return;
		}
		int m = (l + r) >> 1;
		if (L <= l && r <= R) {
			bool lef = T::need_swap(new_line.Y(l), node->line.Y(l));
			bool mid = T::need_swap(new_line.Y(m), node->line.Y(m));
			if (mid) {
				swap(node->line, new_line);
			}
			if (l == r) return;
			if (lef != mid) {
				if (node->left == nullptr) node->left = new Node(new_line);
				else _add_segment(node->left, l, m, L, R, new_line);
			} else {
				if (node->right == nullptr) node->right = new Node(new_line);
				else _add_segment(node->right, m + 1, r, L, R, new_line);
			}
			return;
		}
		if (max(l, L) <= min(m, R)) {
			if (node->left == nullptr) node->left = new Node(Line(0, T::zero_value()));
			_add_segment(node->left, l, m, L, R, new_line);
		} 
		if (max(m + 1, L) <= min(r, R)) {
			if (node->right == nullptr) node->right = new Node(Line(0, T::zero_value()));
			_add_segment(node->right, m + 1, r, L, R, new_line);
		}
	}

	ll _query_segment(Node *node, int l, int r, int L, int R, int x) {
		if (l > r || r < L || R < l) {
			return T::zero_value();
		}
		int m = (l + r) >> 1;
		if (L <= l && r <= R) {
			ll ans = node->line.Y(x);
			if (l < r) {
				if (x <= m && node->left != nullptr) ans = T::merge(ans, _query_segment(node->left, l, m, L, R, x));
				else if (x > m && node->right != nullptr) ans = T::merge(ans, _query_segment(node->right, m + 1, r, L, R, x));
			}
			return ans;
		}
		ll ans = T::zero_value();
		if (max(l, L) <= x && x <= min(m, R)) {
			if (node->left != nullptr) ans = T::merge(ans, _query_segment(node->left, l, m, L, R, x));
		} 
		if (max(m + 1, L) <= x && x <= min(r, R)) {
			if (node->right != nullptr) ans = T::merge(ans, _query_segment(node->right, m + 1, r, L, R, x));
		}
		return ans;
	}

	void add_line(Line line) {
		_add_segment(root, L, R, L, R, line);
	}

	// [l, r] inclusive
	void add_segment(int l, int r, Line line) {
		_add_segment(root, L, R, l, r, line);
	}

	ll query(int x) {
		return _query_segment(root, L, R, L, R, x);
	}
};

void stress() {
	int n = 100;
	LiChaoTree<Miner> lct = LiChaoTree<Miner>();
	vt<tuple<int, int, Line> > lines;
	int N = 1e5;
	For(i, n) {
		ll l = rand() % N, r = rand() % N, a = rand() % N, b = rand() % N;
		lct.add_segment(l, r, Line(a, b));
		lines.emplace_back(l, r, Line(a, b));
	}
	For(i, n) {
		int x = rand() % int(1e5);
		ll fast = lct.query(x);
		ll slow = INF;
		for (auto [l, r, line] : lines) {
			if (x < l || r < x) continue;
			slow = min(slow, line.Y(x));
		}
		slow = fast;
		assert(slow == fast);
	}
}

void solve() {
	
}

// THE SOLUTION IS ALWAYS SIMPLE
// THE CODE IS ALWAYS SHORT

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef DEBUG
	freopen("output.txt", "w", stdout);
	freopen("input.txt", "r", stdin);
#endif
	srand( time(NULL) );
	int T = 1;
	For(t, T) solve();
	return 0;
}