#include <bits/stdc++.h>

using namespace std;

#define For(i, n)           for(int i = 0; i < n; ++i)
#define qFor(i, x, n)       for(int i = x; i < n; ++i)
#define all(x)              (x).begin(),(x).end()
#define rall(x)             (x).rbegin(),(x).rend()

#define ld                  long double
#define pii                 pair<int, int>
#define vt                  vector
#define ll                  long long
// #define endl                '\n'

#define DEBUG
#ifdef DEBUG
#define dout(str)           do {cout << "! " << str << endl;} while(false)
#else
#define dout(str)           do { } while ( false )
#endif

const int MAX = 1e9;
const int MOD = 1e9 + 7;
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

struct commit {
    int pu = 0, pv = 0, szu = 0;
    int dec = 1;
    commit(int pu, int pv, int szu) {
        this->pu = pu;
        this->pv = pv;
        this->szu = szu;
    }
    commit(int dec) {
        this->dec = 0;
    }
    void roll_back() {
        
    }
};

const int N = 5e4 + 5;
vt<int> p(N), sz(N, 1);
vt<commit> history;

int get(int v) {
    if (v == p[v]) return v;
    return get(p[v]);
}

void join(int u, int v, vt<commit> & history) {
    int pu = get(u), pv = get(v);
    if (sz[pv] < sz[pu]) {
        history.push_back(commit(pu, pv, sz[pu]));
        p[pv] = pu;
        sz[pu] += sz[pv];
    } else {
        history.push_back(commit(pv, pu, sz[pv]));
        p[pu] = pv;
        sz[pv] += sz[pu];
    }
} 

void init() {
    iota(all(p), 0);
    fill(all(sz), 1);
    history.clear();
}

bool cmp_by_f_s(pair<pii, int> & a, pair<pii, int> & b) {
    return a.first.second < b.first.second;
}

void solve()
{
    int n, m; cin >> n >> m;
    vt<pii> e(m);
    For(i, m) {
        int x, y; cin >> x >> y; x--, y--;
        e[i].first = x, e[i].second = y;
    }

    int k; cin >> k;
    vt<pair<pii, int> > qe(k);
    For(i, k) {
        int l, r; cin >> l >> r; l--, r--;
        qe[i].first.first = l, qe[i].first.second = r, qe[i].second = i;
    }
    sort(all(qe));
    int sq = sqrt(m);
    int size = m / sq + 1;
    vt<vt<pair<pii, int> > > buckets(size);
    for (int i = 0; i < k; i++) {
        int pos = qe[i].first.first / sq;
        buckets[pos].push_back(qe[i]);
    }

    for (int i = 0; i < size; i++) {
        sort(all(buckets[i]), cmp_by_f_s);
    }
    vt<int> ans(k);
    for (int i = 0; i < size; i++) {
        int next = (i + 1) * sq;
        init();
        int last = -1;
        int prev = -1;
        int cnt = n;
        for (auto x : buckets[i]) {
            if (x.first.second < next) {
                int lcnt = n;
                for (int j = x.first.first; j <= x.first.second; j++) {
                    pii edj = e[j];
                    if (get(edj.first) != get(edj.second)) {
                        join(edj.first, edj.second, history);
                        lcnt--;
                    } else {
                        history.push_back(commit(0));
                    }
                }
                ans[x.second] = lcnt;
                for (int j = x.first.first; j <= x.first.second; j++) {
                    commit cm = history.back();
                    if (cm.dec != 0) {
                        p[cm.pv] = cm.pv;
                        sz[cm.pu] = cm.szu; 
                        lcnt++;
                    }
                    history.pop_back();
                }
            } else {
                int mx = max(last, next) + 1;
                if (prev != -1) {
                    for (int j = prev; j <= next; j++) {
                        commit cm = history.back();
                        if (cm.dec != 0) {
                            p[cm.pv] = cm.pv;
                            sz[cm.pu] = cm.szu; 
                            cnt++;
                        }
                        history.pop_back();
                    }
                }
                for (int j = mx; j <= x.first.second; j++) {
                    pii edj = e[j];
                    if (get(edj.first) != get(edj.second)) {
                        join(edj.first, edj.second, history);
                        cnt--;
                    } else {
                        history.push_back(commit(0));
                    }
                }
                for (int j = x.first.first; j <= next; j++) {
                    pii edj = e[j];
                    if (get(edj.first) != get(edj.second)) {
                        join(edj.first, edj.second, history);
                        cnt--;
                    } else {
                        history.push_back(commit(0));
                    }
                }
                last = x.first.second;
                prev = x.first.first;
                ans[x.second] = cnt;
            }
        }
    }
    For(i, k) cout << ans[i] << endl;
}   

 
int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
// #define FILE
#ifdef FILE
    freopen("output.txt", "w", stdout);
    freopen("input.txt", "r", stdin);
#endif
    cout << setprecision(20) << fixed;
    int T = 1;
    For(t, T) {
        solve();
    }
    return 0;
}