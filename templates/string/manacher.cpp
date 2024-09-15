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

vector<int> manacher(string s) {
	int n = s.size();
	s = "@" + s + "$";
	vector<int> len(n + 1);
	int l = 1, r = 1;
	for(int i = 1; i <= n; i++) {
		len[i] = min(r - i, len[l + (r - i)]);
		while (s[i - len[i]] == s[i + len[i]]) {
			len[i]++;
		}
		if (i + len[i] > r) {
			l = i - len[i];
			r = i + len[i];
		}
	}
	len.erase(begin(len));
	return len;
}

vt<vt<bool> > is_pal(string s) {
	int n = s.length();
	vt<vt<bool> > is_pal(n, vt<bool> (n));
	for (int i = 0; i < n; i++) {
		for (int r = 0; i - r >= 0 && i + r < n; r++) {
			if (s[i - r] != s[i + r]) break;
			is_pal[i - r][i + r] = true;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int r = 0; i - r >= 0 && i + r + 1 < n; r++) {
			if (s[i - r] != s[i + r + 1]) break;
			is_pal[i - r][i + r + 1] = true;
		}
	}
	return is_pal;
}

void solve() {
	string s; cin >> s;
	vt<int> res = manacher(s);
	print(res);
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solve();
	return 0;
}