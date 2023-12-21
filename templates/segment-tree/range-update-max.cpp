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

const int NEED_PUSH = 0, EMPTY = -1;

struct seg_tree_push {
	int n;
	vt<int> lazy, tree;

    seg_tree_push() {}

	seg_tree_push(int n) {
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
            int tm = tl + tr >> 1;
            _update(ls(v), tl, tm, l, min(r, tm), color);
            _update(rs(v), tm+1, tr, max(l, tm+1), r, color);
            tree[v] = max(tree[ls(v)], tree[rs(v)]);
        }
    }

    void update(int l, int r, int color) {
        _update(0, 0, n-1, l, r, color);
    }

    int _get(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return -MAX;
        if (l == tl && tr == r)
            return tree[v];
        push(v);
        int tm = tl + tr >> 1;
        return max(_get(ls(v), tl, tm, l, min(r, tm)), 
                _get(rs(v), tm+1, tr, max(l, tm+1), r));
    }

    int get(int l, int r) {
        return _get(0, 0, n-1, l, r);
    }
};

void solve()
{
    int n; cin >> n;
    seg_tree_push tree = seg_tree_push(n);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}