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

struct sorter {
	ll inv_cnt = 0;
	vt<int> a;

	sorter(vt<int> a) {
		this->a = a;
	}
	
	void merge_sort(int l, int r) {
		if (l >= r) {
			return;
		}
		int m = (l + r) / 2;
		merge_sort(l, m);
		merge_sort(m + 1, r);
	
		int l2 = l, m2 = m + 1;
		vt<int> b;
	
		while (l2 <= m && m2 <= r) {
			if (a[l2] <= a[m2]) { // be carefull with this value, for not unique values
				b.push_back(a[l2]); 
				l2++;
			} else {
				b.push_back(a[m2]); 
				inv_cnt += m - l2 + 1;
				m2++;
			}
		}
		
		while (l2 <= m) {
			b.push_back(a[l2]);
			l2++;
		}
		
		while (m2 <= r) {
			b.push_back(a[m2]);
			m2++;
		}
	
		for (int i = l; i <= r; i++) {
			a[i] = b[i - l];
		}
	}
};

void solve() {
	
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solve();
	return 0;
}