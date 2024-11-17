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

struct MultiDynamicMex {
	int N;
	set<int> st;
	unordered_map<int, int> cnt;

	MultiDynamicMex() {}
	
	MultiDynamicMex(int N) {
		this->N = N;
		this->fill();
	}
	
	void fill() {
		for (int i = 0; i <= N + 1; i++) {
			st.insert(i);
		}
	}
	
	int mex() {
		return *st.begin();
	}
	
	void remove(int x) {
		if (x > N || cnt[x] == 0 || (cnt[x]-=1) != 0) return;
		st.insert(x);
	}

	void add(int x) {
		if (x > N) return;
		cnt[x]++;
		if (st.count(x) == 0) return;
		st.erase(x);
	}
};

void solve() {
	
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solve();
	return 0;
}