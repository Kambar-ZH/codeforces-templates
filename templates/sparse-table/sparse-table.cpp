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

template<typename N>
struct Maxer {
	static N merge(N & n1, N & n2) {
		N r(max(n1, n2));
		return r;
	}
};

template<typename N, typename M>
struct SparseTable
{
	int n;
	vt<vt<N> > dp;
	vt<int> prec_lg2;

	SparseTable(vector<N> &a) {
		this->n = a.size();
		dp = vt<vt<N> > (n, vt<N> (log2(n) + 1));
		prec_lg2 = vt<int> (n + 1);
		init(a);
	}

	void init(vector<N> &a) {
		for(int i = 2; i <= n; i++) {
			prec_lg2[i] = prec_lg2[i >> 1] + 1;
		}
		for(int i = 0; i < n; i++) {
			dp[i][0] = a[i];
		}
		for(int j = 1; (1 << j) <= n; j++) {
			for(int i = 0; i < n; i++) {
				dp[i][j] = dp[i][j - 1];
				int shift = i + (1 << (j - 1));
				if (shift < n) {
					dp[i][j] = M::merge(dp[i][j - 1], dp[shift][j - 1]);
				}
			}
		}
	}

	N get(int l, int r) {
		int k = prec_lg2[r - l + 1];
		return M::merge(dp[l][k], dp[r - (1 << k) + 1][k]);
	}
};

void solve() {
	int n; cin >> n;
	vt<int> a(n); read(a);
	auto tree = SparseTable<int, Maxer<int> >(a);
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solve();
	return 0;
}