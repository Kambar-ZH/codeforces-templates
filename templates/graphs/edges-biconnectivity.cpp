#include <bits/stdc++.h>
using namespace std;
#define pb(i)               push_back(i)
#define For(i, n)           for(int i = 0; i < n; ++i)
#define qFor(i, x, n)       for(int i = x; i < n; ++i)
#define rFor(i, n)          for(int i = n - 1; i >= 0; --i)
#define see                 cout << endl
#define all(x)              (x).begin(),(x).end()
#define rall(x)             (x).rbegin(),(x).rend()
#define pii                 pair<int, int>
#define vt                  vector
#define ll                  long long
#define ld                  long double

const int N = 2e3 + 10;
vt<vt<pii> > g(N);
vt<pii> edges(N);
vt<int> used(N), colors(N), fup(N), tin(N);
int maxColor = 1;
int timer = 1;

void clear(int n) {
	maxColor = timer = 1;
	For(i, n) {
		used[i] = colors[i] = fup[i] = tin[i] = 0;
		g[i].clear();
	}
}

void paint(int v, int color) {
	colors[v] = color;
	for (pii pr : g[v]) {
        int to = pr.first;
		if (colors[to] != 0) continue;

		if (fup[to] > tin[v]) {
			paint(to, ++maxColor);
		} else {
			paint(to, color);
		}
	}
}

void dfs(int v, int p = -1) {
	used[v] = true;
	tin[v] = fup[v] = timer++;
	for (pii pr : g[v]) {
        int to = pr.first;
		if (to == p) continue;
		if (used[to]) {
			fup[v] = min(fup[v], tin[to]);
		} else {
			dfs(to, v);
			fup[v] = min(fup[v], fup[to]);
		}
	}
}

void solve()
{
	int n, m; cin >> n >> m;
    clear(n);
	For(i, m) {
		int f, t;
		cin >> f >> t; f--, t--;
        edges[i] = {f + 1, t + 1};
		g[f].push_back({t, i});
		g[t].push_back({f, i});
	}
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			dfs(i);
		}
	}
	for (int i = 0; i < n; i++) {
		if (!colors[i]) {
			paint(i, maxColor);
		}
	}
	vt<vt<int> > colors2(maxColor);
	For(v, n) {
        colors2[colors[v] - 1].push_back(v);
	}
}
 
int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef DEBUG
	freopen("output.txt", "w", stdout);
	freopen("input.txt", "r", stdin);
#endif
	int T;
	T = 1;
	cin >> T;
	For(t, T) solve();
	return 0;
}