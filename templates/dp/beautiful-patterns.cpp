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

const int MAX = 1e9;
const int MOD = 1e9+7;
const ll  INF = 1e18;
const ld  PI  = 3.14159265358979323846;

void solve() {
    int n, m; cin >> n >> m;
    if (n > m) swap(n, m);
    int N = (1 << n);
    
    vt<vt<char> > transition(N, vt<char> (N, 1));

    For(i, N) {
        For(j, N) {
            int ii = i, jj = j;
            int cnt = 0, last = -1;
            for (int b = 0; b < n; b++, ii >>= 1, jj >>= 1) {
                int b1 = (ii & 1), b2 = (jj & 1);
                if (b1 != b2) {
                    cnt = 0;
                    last = -1;
                    continue;
                }
                if (b1 != last) {
                    cnt = 0;
                    last = b1;
                }
                cnt++;
                if (cnt == 2) {
                    transition[i][j] = 0;
                    break;
                }
            }
        }
    }

    vt<vt<int> > dp(m, vt<int> (N));
    For(i, N) {
        dp[0][i] = 1;
    }

    for (int k = 1; k < m; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (!transition[j][i]) continue;
                dp[k][i] += dp[k - 1][j];
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < N; i++) {
        ans += dp[m - 1][i];
    }

    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}