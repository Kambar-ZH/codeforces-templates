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

const int N = 905, M = 8105;
vt<vt<bool> > visited(N, vt<bool> (M, false));
vt<vt<int> > dp(N, vt<int> (M, MAX)); // optimize the length of the number
vt<vt<int> > ch(N, vt<int> (M, MAX)); // save the minimal digit

int go(int s1, int s2) {
	if (s1 < 0 || s2 < 0) {
		return MAX;
	}
	if (s1 == 0 && s2 == 0) {
		return dp[s1][s2] = 0;
	}
	if (visited[s1][s2]) {
		return dp[s1][s2];
	}
	visited[s1][s2] = true;
	for (int i = 1; i <= 9; i++) {
		int res = go(s1 - i, s2 - i * i);
		if (res + 1 < dp[s1][s2]) {
			dp[s1][s2] = res + 1;
			ch[s1][s2] = i;
		}
	}
	return dp[s1][s2];
}

void solve() {
	int s1, s2; cin >> s1 >> s2;
	if (s1 > 900 || s2 > s1 * 9) {
		cout << "No solution" << endl;
		return;
	}

	if (go(s1, s2) <= 100) {
		string str = "";
		while (s1 != 0 || s2 != 0) {
			int c = ch[s1][s2];
			str.push_back(char('0' + c));
			s1 -= c, s2 -= c * c;
		}
		cout << str << endl;
		return;
	}
	cout << "No solution" << endl;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solve();
	return 0;
}