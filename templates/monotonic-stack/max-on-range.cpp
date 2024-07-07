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

// https://codeforces.com/contest/1156/problem/E
// https://codeforces.com/contest/1849/problem/E

void solve() {
    int n; cin >> n;
    vt<int> p(n); read(p);
    For(i, n) p[i]--;
    vt<int> pos(n);
    For(i, n) pos[p[i]] = i;
    vt<int> mx_lb(n, -1), mx_rb(n, n);
    stack<int> mx_st;
    for (int i = 0; i < n; i++) {
        while (!mx_st.empty() && p[mx_st.top()] < p[i]) {
            mx_st.pop();
        }
        mx_lb[i] = (mx_st.empty() ? -1 : mx_st.top());
        mx_st.push(i);
    }
    mx_st = stack<int> ();
    for (int i = n - 1; i >= 0; i--) {
        while (!mx_st.empty() && p[mx_st.top()] < p[i]) {
            mx_st.pop();
        }
        mx_rb[i] = (mx_st.empty() ? n : mx_st.top());
        mx_st.push(i);
    }
    int ans = 0;
    // works in N * log2(N)
    for (int i = 0; i < n; i++) {
        if (i - mx_lb[i] < mx_rb[i] - i) {
            for (int j = mx_lb[i] + 1; j < i; j++) {
                int pos_need = pos[p[i] - p[j] - 1];
                ans += (i < pos_need && pos_need < mx_rb[i]);
            }
        } else {
            for (int j = i + 1; j < mx_rb[i]; j++) {
                int pos_need = pos[p[i] - p[j] - 1];
                ans += (mx_lb[i] < pos_need && pos_need < i);
            }
        }
    }
    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}