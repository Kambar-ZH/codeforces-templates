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

struct Calculator {
    int ans = 0;
    int l = 0, r = -1;
    vt<int> pre, nxt;

    Calculator() {}

    Calculator(vt<int> _pre, vt<int> _nxt) {
        pre = _pre;
        nxt = _nxt;
    }

    void add_left() {
        ans += nxt[l - 1] > r;
        l--;
    }

    void add_right() {
        ans += pre[r + 1] < l;
        r++;
    }

    void remove_left() {
        ans -= nxt[l] > r;
        l++;
    }

    void remove_right() {
        ans -= pre[r] < l;
        r--;
    }

    int get_ans() {
        return ans;
    }
};

// block_size should be little more than sqrt(N) by some constant factor 
int block_size = 500;

struct MO {
    Calculator c;

    MO () {}

    MO (Calculator c) : c(c) {}

    struct Query {
        int l, r, idx;
        bool operator<(Query other) const {
            return make_pair(l / block_size, r) <
                make_pair(other.l / block_size, other.r);
        }
    };

    vt<int> solve(vt<Query> queries) {
        vt<int> answers(queries.size());
        sort(queries.begin(), queries.end());

        // invariant: data structure will always reflect the range [curL, curR]
        for (Query q : queries) {
            while (c.l > q.l) c.add_left();
            while (c.r < q.r) c.add_right();
            while (c.l < q.l) c.remove_left();
            while (c.r > q.r) c.remove_right();
            answers[q.idx] = c.get_ans();
        }

        return answers;
    }
};

void solve() {
    int n; cin >> n;
    vt<int> a(n); read(a);
    vt<int> pre(n, -1), nxt(n, n);
    unordered_map<int, int> mp;
    For(i, n) {
        if (mp.find(a[i]) != mp.end()) {
            pre[i] = mp[a[i]];
        }
        mp[a[i]] = i;
    }
    mp.clear();
    for (int i = n - 1; i >= 0; i--) {
        if (mp.find(a[i]) != mp.end()) {
            nxt[i] = mp[a[i]];
        }
        mp[a[i]] = i;
    }
    Calculator c = Calculator(pre, nxt);
    MO mo = MO(c);
    vt<MO::Query> queries;

    int q; cin >> q;
    For(i, q) {
        int l, r; cin >> l >> r; l--, r--;
        queries.push_back(MO::Query{l, r, i});
    }

    vt<int> ans = mo.solve(queries);
    For(i, q) {
        cout << ans[i] << endl;
    }
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