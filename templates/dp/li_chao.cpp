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
const ll  INF = 2e18;
const ld  PI  = 3.14159265358979323846;

struct Line {
    ll a, b;
    Line(ll a, ll b) : a(a), b(b) {}

    ll Y(ll x) {
        return a * x + b;
    }
};

struct Node {
    Line line;
    Node *left = nullptr, *right = nullptr;

    Node(Line line) : line(line) {}

    void add_segment(int l, int r, int L, int R, Line new_line) {
        if (l > r || r < L || R < l) {
            return;
        }
        int m = (l + r) >> 1;
        if (L <= l && r <= R) {
            bool lef = new_line.Y(l) < line.Y(l);
            bool mid = new_line.Y(m) < line.Y(m);
            if (mid) {
                swap(line, new_line);
            }
            if (l == r) return;
            if (lef != mid) {
                if (left == nullptr) left = new Node(new_line);
                else left->add_segment(l, m, L, R, new_line);
            } else {
                if (right == nullptr) right = new Node(new_line);
                else right->add_segment(m + 1, r, L, R, new_line);
            }
            return;
        }
        if (max(l, L) <= min(m, R)) {
            if (left == nullptr) left = new Node(Line(0, INF));
            left->add_segment(l, m, L, R, new_line);
        } 
        if (max(m + 1, L) <= min(r, R)) {
            if (right == nullptr) right = new Node(Line(0, INF));
            right->add_segment(m + 1, r, L, R, new_line);
        }
    }

    ll query_segment(int l, int r, int L, int R, int x) {
        if (l > r || r < L || R < l) {
            return INF;
        }
        int m = (l + r) >> 1;
        if (L <= l && r <= R) {
            ll ans = line.Y(x);
            if (l < r) {
                if (x <= m && left != nullptr) ans = min(ans, left->query_segment(l, m, L, R, x));
                else if (x > m && right != nullptr) ans = min(ans, right->query_segment(m + 1, r, L, R, x));
            }
            return ans;
        }
        // not tested
        ll ans = INF;
        if (max(l, L) <= x && x <= min(m, R)) {
            if (left != nullptr) ans = min(ans, left->query_segment(l, m, L, R, x));
        } 
        if (max(m + 1, L) <= x && x <= min(r, R)) {
            if (right != nullptr) ans = min(ans, right->query_segment(m + 1, r, L, R, x));
        }
        return ans;
    }
};

struct LiChaoTree {
    ll L, R;
    Node *root = nullptr;

    LiChaoTree() {
        L = -INF, R = INF, root = new Node(Line(0, INF));
    }

    void add_line(Line line) {
        root->add_segment(L, R, L, R, line);
    }

    // [l, r]
    void add_segment(int l, int r, Line line) {
        root->add_segment(L, R, l, r, line);
    }

    ll query(int x) {
        return root->query_segment(L, R, L, R, x);
    }
};

void solve() {
    int n, q; cin >> n >> q;
    LiChaoTree tree = LiChaoTree();
    For(i, n) {
        int l, r, a; ll b; cin >> l >> r >> a >> b; r--;
        tree.add_segment(l, r, Line(a, b));
    }
    For(i, q) {
        int qt; cin >> qt;
        if (qt == 0) {
            int l, r, a; ll b; cin >> l >> r >> a >> b; r--;
            tree.add_segment(l, r, Line(a, b));
        } else {
            int x; cin >> x;
            ll res = tree.query(x);
            cout << ((res == INF) ? ("INFINITY") : to_string(res)) << endl;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}