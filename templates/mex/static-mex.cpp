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

struct StaticMex {
	int N;
	vt<bool> used;

	StaticMex() {}
	
	StaticMex(int N) {
		this->N = N;
		this->used.assign(N + 1, false);
	}

	int mex(const vector<int> & a) {
		int n = a.size();
		for (int i = 0; i < n; i++) {
			if (a[i] <= N) {
				used[a[i]] = true;
			}
		}
		int result = -1;
		for (int i = 0; ; i++) {
			if (!used[i]) {
				result = i;
				break;
			}
		}
		for (int i = 0 ; i < n; i++) {
			if (a[i] <= N) {
				used[a[i]] = false;
			}
		}
		return result;
	}
};

void solve() {
	
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solve();
	return 0;
}