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

template<typename T>
void read(vt<T> & a) {For(i, a.size()) cin >> a[i];}
template<typename T>
void read2(vt<vt<T> > & a) {For(i, a.size()) read(a[i]);}
template<typename T>
void print(vt<T> & a) {For(i, a.size()) cout << a[i] << " "; cout << endl;}
template<typename T>
void print2(vt<vt<T> > & a) {For(i, a.size()) print(a[i]);}

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
const int MOD = 1e9+7;
const ll  INF = 1e18;
const ld  PI  = 3.14159265358979323846;

struct edge {
    int a, b, l, r;
};

struct operation {
    char type; 
    int a, b;
};

struct dynamic_connectivity {
    int n, k;
    vt<int> cnt, ans, color, used, deg;
    vt<vt<int> > g;

    dynamic_connectivity(int n, int k) {
        this->n = n;
        this->k = k;
        this->cnt = vt<int> (k + 1);
        this->ans = vt<int> (k);
        this->color = vt<int> (n);
        this->used = vt<int> (n);
        this->deg = vt<int> (n);
        this->g = vt<vt<int> > (n);
    }

    vt<int> get_ans(vt<operation> & ops) {
        map<pii, int> mp;
        vt<edge> list;
        for (int i = 0; i < ops.size(); i++) {
            operation op = ops[i];
            if (op.type == '?') {
                cnt[i + 1]++;
                cnt[i + 1] += cnt[i];
                continue;
            }
            cnt[i + 1] += cnt[i];
            if (op.a > op.b) swap(op.a, op.b);
            if (op.a == op.b) {
                i--, k--;
                continue;
            }
            pii p = pii(op.a, op.b);
            if (op.type == '+') {
                mp[p] = i;
            } else {
                list.push_back(edge{op.a, op.b, mp[p], i});
                mp[p] = -1;
            }
        }
        for (auto & [key, v] : mp) {
            if (v != -1) {
                list.push_back(edge{key.first, key.second, v, k});
            }
        }

        this->go(list);

        vt<int> ans;
        For(i, k) {
            if (cnt[i] != cnt[i + 1]) {
                ans.push_back(this->ans[i]);
            }
        }
        return ans;
    }

    void dfs(int v, int value) {
        used[v] = 1, color[v] = value;
        for (int u : g[v]) {
            if (used[u]) continue;
            dfs(u, value);
        }
    }

    void _go(int l, int r, const vt<edge> & list, int vn, int add_vn) { // [l, r)
        if (cnt[l] == cnt[r]) return;
        if (list.empty()) {
            for (int i = l; i < r; i++) {
                ans[i] = vn + add_vn;
            }
            return;
        }
        vt<edge> list2;
        for (int i = 0; i < vn; i++) {
            g[i].clear();
        }
        for (edge e : list) {
            if (e.a == e.b) continue;

            if (e.l <= l && r <= e.r) {
                g[e.a].push_back(e.b);
                g[e.b].push_back(e.a);
            } else if (l < e.r && e.l < r) {
                list2.push_back(e);
            }
        }
        int vn2 = 0;
        for (int i = 0; i < vn; i++) {
            used[i] = 0;
        }
        for (int i = 0; i < vn; i++) {
            if (used[i]) continue;
            deg[vn2] = 0, dfs(i, vn2++);
        }
        for (edge & e : list2) {
            e.a = color[e.a];
            e.b = color[e.b];
            if (e.a == e.b) continue;
            deg[e.a]++, deg[e.b]++;
        }
        
        vn = vn2, vn2 = 0;
        for (int i = 0; i < vn; i++) {
            color[i] = vn2, vn2 += (deg[i] > 0), add_vn += (deg[i] == 0);  
        }
        for (edge & e : list2) {
            e.a = color[e.a];
            e.b = color[e.b];
        }

        int m = (l + r) >> 1;
        _go(l, m, list2, vn2, add_vn);
        _go(m, r, list2, vn2, add_vn);
    }

    void go(const vt<edge> & list) {
        _go(0, k, list, n, 0);
    }
};

void solve() {
    int n, k; cin >> n >> k;
    vt<operation> ops(k);
    For(i, k) {
        cin >> ops[i].type;
        if (ops[i].type == '?') {
            continue;
        }
        cin >> ops[i].a >> ops[i].b; ops[i].a--, ops[i].b--;
    }
    dynamic_connectivity dc = dynamic_connectivity(n, k);
    vt<int> ans = dc.get_ans(ops);
    print(ans);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}