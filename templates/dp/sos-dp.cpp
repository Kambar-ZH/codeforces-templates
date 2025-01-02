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

const pair<int, int> invalid = pair(-1, -1);

// https://codeforces.com/gym/105633/problem/K

void solve() {
    int n, m; cin >> n >> m;
    vt a = vt(n, vt (m, ' ')); read2(a);
    int M = (1 << m);
    vt F = vt(M, invalid);
    vt A = vt(n, invalid);
    For(i, n) {
        int mask = 0;
        int cnt = 0;
        For(j, m) {
            if (a[i][j] == 'N') continue;
            mask |= (1 << j);
            cnt++;
        }
        int inv_mask = (M - 1) - mask;
        A[i] = pair(mask, cnt);
        if (F[inv_mask].first >= cnt) continue;
        F[inv_mask] = pair(cnt, i);
    }
    for (int b = 0; b < m; b++) {
        for (int mask = 0; mask < M; mask++) {
            if (mask & (1 << b)) {
                auto before = F[mask ^ (1 << b)];
                if (F[mask].first < before.first) {
                    F[mask] = before;
                } else if (F[mask].first == before.first && F[mask].second > before.second) {
                    F[mask] = before;
                }
            }
        }
    }
    pair<int, pii> ans = pair(-1, invalid);
    for (int i = 0; i < n; i++) {
        auto [mask, cnt] = A[i];
        if (F[mask] == invalid) {
            continue;
        }
        int mn = min(i, F[mask].second);
        int mx = max(i, F[mask].second);
        if (mn == mx) continue;
        auto temp = pair(cnt + F[mask].first, pair(mn, mx));
        if (ans.first > temp.first) continue;
        if (ans.first < temp.first) {
            ans = temp;
            continue;
        }
        if (ans.second.first < temp.second.first) continue;
        if (ans.second.first > temp.second.first) {
            ans = temp;
            continue;
        }
        if (ans.second.second > temp.second.second) {
            ans = temp;
        }
    }
    if (ans.first < m) {
        cout << "No" << endl;
        return;
    }
    cout << ans.second.first + 1 << " " << ans.second.second + 1 << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}