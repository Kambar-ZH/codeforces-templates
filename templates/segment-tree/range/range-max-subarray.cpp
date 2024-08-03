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

template<typename T> void read(vt<T> & a) {For(i, a.size()) cin >> a[i];}
template<typename T> void read2(vt<vt<T> > & a) {For(i, a.size()) read(a[i]);}
template<typename T> void print(vt<T> & a) {For(i, a.size()) cout << a[i] << " "; cout << endl;}
template<typename T> void print2(vt<vt<T> > & a) {For(i, a.size()) print(a[i]);}

const int MAX = 1e9;
const int MOD = 1000000007;
const ll  INF = 1e18;
const ld  PI  = 3.14159265358979323846;

struct node {
	int sum, pref, suff, ans;
    bool need_push;
    int lazy;
    node() {
        this->sum = this->pref = this->suff = this->ans = 0;
        this->need_push = false;
        this->lazy = 0;
    }
	node(int value) {
        this->sum = value;
        this->pref = this->suff = this->ans = max(0, value);
        this->need_push = false;
        this->lazy = 0;
    }
};

template<typename N>
struct summer {
	static N merge(N n1, N n2) {
        N r;
        r.sum = n1.sum + n2.sum;
        r.pref = max (n1.pref, n1.sum + n2.pref);
        r.suff = max (n2.suff, n2.sum + n1.suff);
        r.ans = max (max (n1.ans, n2.ans), n1.suff + n2.pref);
		return r;
	}
};

template<typename N, typename M>
struct seg_tree_push {
    int n;
    vt<N> tree;
    seg_tree_push() {}

    seg_tree_push(int n) {
        this->n = n;
        this->tree = vt<N> (n << 2);
    }

    void push_to_node(int x, int lx, int rx, int k) {
        tree[x].sum = (rx - lx + 1) * k;
        tree[x].pref = tree[x].suff = tree[x].ans = std::max(tree[x].sum, 0);
        tree[x].lazy = k, tree[x].need_push = true;
    }

    void push_to_childs(int x, int lx, int rx) {
        if(!tree[x].need_push) return;
        int mx = (lx + rx) >> 1;
        push_to_node(ls(x), lx, mx, tree[x].lazy);
        push_to_node(rs(x), mx+1, rx, tree[x].lazy);
        tree[x].lazy = 0, tree[x].need_push = false;
    }

	N _get(int x, int lx, int rx, int l, int r) {
		if (l == lx && rx == r) {
			return tree[x];
		}

		push_to_childs(x, lx, rx);

		int mx = (lx + rx) >> 1;

        if (r <= mx) {
            return _get(ls(x), lx, mx, l, r);
        }
        if (l > mx) {
            return _get(rs(x), mx + 1, rx, l, r);
        }

		return M::merge(_get(ls(x), lx, mx, l, mx),
			_get(rs(x), mx + 1, rx, mx + 1, r));
	}

    N get(int l, int r) {
        return _get(0, 0, n - 1, l, r);
    }

	void _update(int x, int lx, int rx, int l, int r, N & val) {
        if (r < lx || rx < l) {
            return;
        }
        
        if (l == lx && rx == r) {
            push_to_node(x, lx, rx, val.sum);
            return;
        }
        
        push_to_childs(x, lx, rx);

        int mx = (lx + rx) >> 1;
        
        _update(ls(x), lx, mx, l, min(r, mx), val);
        _update(rs(x), mx + 1, rx, max(l, mx + 1), r, val);

        tree[x] = M::merge(tree[ls(x)], tree[rs(x)]);
    }

    void update(int l, int r, N & val) {
        _update(0, 0, n - 1, l, r, val);
    }
};

void solve() {
    
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}