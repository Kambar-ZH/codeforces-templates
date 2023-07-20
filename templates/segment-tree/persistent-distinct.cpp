#include <bits/stdc++.h>

using namespace std;

#define For(i, n)           for(int i = 0; i < n; ++i)
#define see                 cout << endl;
#define all(x)              (x).begin(),(x).end()
#define rall(x)             (x).rbegin(),(x).rend()
#define ls(x)               x+x+1
#define rs(x)               x+x+2

#define ld                  long double
#define pii                 pair<int, int>
#define vt                  vector
#define ll                  long long
// #define endl                '\n'

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

struct node {
    node *left, *right;
    int val;
    node(int val) {
        this->val = val;
        this->left = nullptr;
        this->right = nullptr;
    }
    node() {
        this->val = 0;   
        this->left = nullptr;
        this->right = nullptr;
    }
};

const int N = 1e5+10;
int n, m;
vt<node*> versions(N);

void _build(node *x, int lx, int rx) {
    if (lx == rx) {
        return;
    }
    x->left = new node();
    x->right = new node();
    int mx = (lx + rx) >> 1;
    _build(x->left, lx, mx);
    _build(x->right, mx + 1, rx);
}

void build(node *x) {
    return _build(x, 0, n - 1);
}

node* _update(node *cur, node *prev, int lx, int rx, int id, int v) {
    if (lx == rx) {
        cur = new node(v);
        return cur;
    }
    int mx = (lx + rx) >> 1;

    if (id <= mx) {
        cur->right = prev->right;
        cur->left = _update(new node(), prev->left, lx, mx, id, v);
    } else {
        cur->left = prev->left;
        cur->right = _update(new node(), prev->right, mx + 1, rx, id, v);
    }
    // debug() << imie(cur->left->val) << imie(cur->right->val);
    cur->val = cur->left->val + cur->right->val;
    return cur;
}

node* update(node *cur, node *prev, int id, int v) {
    return _update(cur, prev, 0, n - 1, id, v);
}
 
int _sum(node *x, int lx, int rx, int l, int r) {
    if (r < lx || rx < l) {
        return 0;
    }
    if (l <= lx && rx <= r) {
        return x->val;
    }
    int mx = (lx + rx) >> 1;
    int lst = _sum(x->right, mx + 1, rx, l, r);
    int rst = _sum(x->left, lx, mx, l, r);
    return lst + rst;
}

int sum(node *x, int l, int r) {
    return _sum(x, 0, n - 1, l, r);
}
 
void solve()
{
    cin >> n >> m;
    versions[n] = new node();
    build(versions[n]);
    vt<int> a(n); read(a);
    vt<int> last(n + 1, -1);
    for (int i = n - 1; i >= 0; i--) {
        if (last[a[i]] != -1) {
            node* root = update(new node(), versions[i + 1], last[a[i]], 0);
            last[a[i]] = i;
            versions[i] = update(new node(), root, i, 1);
        } else {
            last[a[i]] = i;
            versions[i] = update(new node(), versions[i + 1], i, 1);
        }
    }
    For(q, m) {
        int l, r; cin >> l >> r; l--, r--;
        cout << sum(versions[l], l, r) << endl;
    }
}

void precalc() { }

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef DEBUG
    freopen("output.txt", "w", stdout);
    freopen("input.txt", "r", stdin);
#endif
    int T;
    T = 1;
    precalc();
    For(t, T) solve();
    return 0;
}