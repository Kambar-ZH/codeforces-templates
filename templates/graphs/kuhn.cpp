#include <bits/stdc++.h>

using namespace std;

#define pb(i)               push_back(i)
#define For(i, n)           for(int i = 0; i < n; ++i)
#define qFor(i, x, n)       for(int i = x; i < n; ++i)
#define rFor(i, n)          for(int i = n - 1; i >= 0; --i)
#define see                 cout << endl;
#define all(x)              (x).begin(),(x).end()
#define rall(x)             (x).rbegin(),(x).rend()

#define ld                  long double
#define pii                 pair<int, int>
#define vt                  vector
#define ll                  long long
// #define endl                '\n'


const int MAX = 1e9;
const int MOD = 1e9 + 7;
const int BINT = 32;
const int BLONG = 64;
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

int n, m, k;
const int N = 105; 
vt<vt<int> > L(N); 
vt<int> R(N, -1);

bool kuhn(int v, vt<bool> & used) {
	if (used[v]) return false;
	used[v] = true;
	for (int to : L[v]) {
		if (R[to] == -1 || kuhn(R[to], used)) {
			R[to] = v;
			return true;
		}
	}
	return false;
}

void solve()
{
	cin >> n;
	vt<int> a(n); read(a);
	cin >> m;
	vt<int> b(m); read(b);
	For(i, n) {
		cout << i + 1 << ": ";
		For(j, m) {
			if (__gcd(a[i], b[j]) == 1) {
				L[i].push_back(j);
				cout << j + 1 << " ";
			}
		}
		cout << endl;
	}
	int cnt = 0;
	For(i, n) {
		vt<bool> used(n);
		if (kuhn(i, used)) cnt++;
	}
	cout << cnt << endl;
}
 
int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef DEBUG
	freopen("output.txt", "w", stdout);
	freopen("input.txt", "r", stdin);
#endif
	int T = 1;
	cin >> T;
	For(t, T) {
		solve();
	}
	return 0;
}