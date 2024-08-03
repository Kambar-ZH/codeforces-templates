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

vt<int> dx = {0, 0, 1, -1};
vt<int> dy = {1, -1, 0, 0};

int in_bound(pii p, int rows, int cols) {
    return 0 <= p.first && p.first < rows && 0 <= p.second && p.second < cols; 
}

int get_index(pii p, int cols) {
    return p.first * cols + p.second;
}

pii get_point(int index, int cols) {
    return pii(index / cols, index % cols);
}

const int W = 200 + 1;

pair<vt<vt<int> >, vt<vt<bitset<W> > > > steiner_tree(vt<int> cost, vt<int> terminals, int rows, int cols) {
    int n = cost.size();
    int k = terminals.size();
    vt dp(1 << k, vt<int>(n, MAX));
    vt dp_nodes(1 << k, vt<bitset<W>> (n));
    for (int i = 0; i < k; i++) {
        dp[1 << i][terminals[i]] = cost[terminals[i]];
        dp_nodes[1 << i][terminals[i]].set(terminals[i]);
    }
    for (int mask = 1; mask < (1 << k); mask++) {
        for (int sub = mask; sub > 0; sub = (sub - 1) & mask) {
            for (int i = 0; i < n; i++) {
                int temp = dp[sub][i] + dp[mask - sub][i] - cost[i];
                if (dp[mask][i] > temp) {
                    dp[mask][i] = temp;
                    dp_nodes[mask][i] = dp_nodes[sub][i] | dp_nodes[mask - sub][i];
                }
            }
        }
        priority_queue<pii, vt<pii>, greater<>> pq;
        for (int i = 0; i < n; i++) pq.emplace(dp[mask][i], i);
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dp[mask][u]) continue;
            for (int i = 0; i < dx.size(); i++) {
                pii pu = get_point(u, cols);
                pii pv = pii(pu.first + dx[i], pu.second + dy[i]);
                if (!in_bound(pv, rows, cols)) continue;
                int v = get_index(pv, cols);
                int cost_v = d + cost[v];
                if (dp[mask][v] > cost_v) {
                    dp[mask][v] = cost_v;
                    dp_nodes[mask][v] = dp_nodes[mask][u];
                    dp_nodes[mask][v].set(v);
                    pq.emplace(cost_v, v);
                }
            }
        }
    }
    return pair(dp, dp_nodes);
}

// https://codeforces.com/contest/152/problem/E

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vt<int> cost;
    For(i, n) {
        For(i, m) {
            int c; cin >> c;
            cost.push_back(c);
        }
    }
    vt<int> terminals;
    For(i, k) {
        int r, c; cin >> r >> c; r--, c--;
        terminals.push_back(get_index(pii(r, c), m));
    }
    auto [dp, dp_nodes] = steiner_tree(cost, terminals, n, m);
    int res = MAX;
    bitset<W> res_bst;
    for (int i = 0; i < n * m; i++) {
        if (res > dp[(1 << k) - 1][i]) {
            res = dp[(1 << k) - 1][i];
            res_bst = dp_nodes[(1 << k) - 1][i];
        }
    }
    vt arr(n, vt<char> (m, '.'));
    for (int i = 0; i < n * m; i++) {
        if (res_bst[i]) {
            auto p = get_point(i, m);
            arr[p.first][p.second] = 'X';
        }
    }
    cout << res << endl;
    For(i, n) {
        For(j, m) {
            cout << arr[i][j];
        }
        cout << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}