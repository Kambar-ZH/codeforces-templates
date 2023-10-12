#include <bits/stdc++.h>

using namespace std;

#define pb(i)               push_back(i)
#define For(i, n)           for(int i = 0; i < n; ++i)
#define qFor(i, x, n)       for(int i = x; i < n; ++i)
#define rFor(i, n)          for(int i = n - 1; i >= 0; --i)
#define see                 cout << endl;
#define all(x)              (x).begin(),(x).end()
#define rall(x)             (x).rbegin(),(x).rend()
#define ls(x)               x+x+1
#define rs(x)               x+x+2

#define ld                  long double
#define pii                 pair<int, int>
#define vt                  vector
#define ll                  long long
#define endl                '\n'
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


const int MAX = 1e9;
const int MOD = 1e9 + 7;
const int BINT = 32;
const int BLONG = 64;
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

const int NEED_PUSH = 0, EMPTY = -1;

struct seg_tree {
	int n;
	vt<int> lazy, tree;
	seg_tree(int n) {
		this->n = n;
		tree.resize(4 * n);
		lazy.resize(4 * n, EMPTY);
	}
 
	void push(int v) {
        if (lazy[v] == NEED_PUSH) {
            tree[ls(v)] = tree[rs(v)] = tree[v];
            lazy[ls(v)] = lazy[rs(v)] = NEED_PUSH;
            lazy[v] = EMPTY;
        }
    }

    void _update(int v, int tl, int tr, int l, int r, int color) {
        if (r < tl || tr < l) {
            return;
        }
        if (l == tl && tr == r) {
            tree[v] = color;
            lazy[v] = NEED_PUSH;
        } else {
            push(v);
            int tm = (tl + tr) / 2;
            _update(ls(v), tl, tm, l, min(r, tm), color);
            _update(rs(v), tm+1, tr, max(l, tm+1), r, color);
            tree[v] = max(tree[ls(v)], tree[rs(v)]);
        }
    }

    void update(int l, int r, int color) {
        _update(0, 0, n-1, l, r, color);
    }

    int _query(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return -MAX;
        if (l == tl && tr == r)
            return tree[v];
        push(v);
        int tm = (tl + tr) / 2;
        return max(_query(ls(v), tl, tm, l, min(r, tm)), 
                _query(rs(v), tm+1, tr, max(l, tm+1), r));
    }

    int query(int l, int r) {
        return _query(0, 0, n-1, l, r);
    }
};

void solve()
{
    int n; cin >> n;
    seg_tree tree = seg_tree(n); // array size
}
 
int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef DEBUG
    freopen("output.txt", "w", stdout);
    freopen("input.txt", "r", stdin);
#endif
    int T;
    T = 1;
    // cin >> T;
    For(t, T) solve();
    return 0;
}