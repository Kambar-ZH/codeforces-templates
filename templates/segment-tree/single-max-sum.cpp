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

struct node {
	ll sum, pref, suff, ans;
    node() {}
	node(ll sum) {
        this->sum = sum;
        this->pref = this->suff = this->ans = max(0LL, sum);
    }
};

template<typename N>
struct summer {
	static N merge(N & n1, N & n2) {
        N r;
        r.sum = n1.sum + n2.sum;
        r.pref = max (n1.pref, n1.sum + n2.pref);
        r.suff = max (n2.suff, n2.sum + n1.suff);
        r.ans = max (max (n1.ans, n2.ans), n1.suff + n2.pref);
		return r;
	}
};

void solve() {
    
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}