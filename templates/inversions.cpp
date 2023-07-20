#include <bits/stdc++.h>

using namespace std;

#define For(i, n)           for(int i = 0; i < n; ++i)
#define all(x)              (x).begin(),(x).end()
#define rall(x)             (x).rbegin(),(x).rend()

#define ld                  long double
#define pii                 pair<int, int>
#define vt                  vector
#define ll                  long long
#define endl                '\n'

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

ll cnt = 0;
 
void merge_sort(int l, int r, vt<int> & a) {
	if (l >= r) {
		return;
	}
	int m = (l + r) / 2;
	merge_sort(l, m, a);
	merge_sort(m + 1, r, a);
 
	int l2 = l, m2 = m + 1;
	vt<int> b;
 
	while (l2 <= m && m2 <= r) {
		if (a[l2] < a[m2]) {
			b.push_back(a[l2]); 
			l2++;
		} else {
			b.push_back(a[m2]); 
			cnt += m - l2 + 1;
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

void solve()
{
    
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
    cin >> T;
    For(t, T) {
        solve();
    }
    return 0;
}