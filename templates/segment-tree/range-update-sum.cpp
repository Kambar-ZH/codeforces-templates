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

struct seg_tree_push {
    int n;
    vt<ll> t;
    vt<int> p, tmax;

    seg_tree_push(int _n) {
        this->n = calc_size(_n);
        this->t = vt<ll> (n << 1, 0);
        this->p = vt<int> (n << 1, -1);
    }

    int calc_size(int _n) {
		int size = 1;
		while (size < _n) size <<= 1;
        return size;
	}

    void push(int v, int tl, int tr) {
        if (p[v] == -1) return;
        if (tl != tr) {
            p[ls(v)] = p[v];
            p[rs(v)] = p[v];
        }
        t[v] = (tr - tl + 1) * 1LL * p[v];
        p[v] = -1;
    }

    void _update(int l, int r, int val, int v, int tl, int tr) {
        push(v, tl, tr);
        if (l <= tl && tr <= r) {
            p[v] = val;
            push(v, tl, tr);
            return;
        }
        if (r < tl || tr < l) {
            return;
        }
        int tm = tl + tr >> 1;
        _update(l, r, val, ls(v), tl, tm);
        _update(l, r, val, rs(v), tm + 1, tr);
        t[v] = t[ls(v)] + t[rs(v)];
        tmax[v] = max(tmax[ls(v)], tmax[rs(v)]);
    }

    void update(int l, int r, int val) {
        return _update(l, r, val, 0, 0, n - 1);
    }
 
    ll _query(int l, int r, int v, int tl, int tr) {
        push(v, tl, tr);
        if (l <= tl && tr <= r) {
            return t[v];
        }
        if (r < tl || tr < l) {
            return 0;
        }
        int tm = tl + tr >> 1;
        return _query(l, r, ls(v), tl, tm) + _query(l, r, rs(v), tm + 1, tr);
    }

    ll query(int l, int r) {
        return _query(l, r, 0, 0, n - 1);
    }
};

void solve() {
    int n; cin >> n;
    seg_tree_push tree = seg_tree_push(n);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}