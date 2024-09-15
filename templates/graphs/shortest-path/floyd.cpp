#include <bits/stdc++.h>

using namespace std;

#define For(i, n)           for(int i = 0; i < n; ++i)
#define all(x)              (x).begin(),(x).end()
#define rall(x)             (x).rbegin(),(x).rend()
#define ls(x)               x+x+1
#define rs(x)               x+x+2
// #define endl                '\n'

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

struct floyd {
	int n;
	vt<vt<int> > g, p;
	
	floyd(vt<vt<int> > g) {
		this->n = g.size();
		this->g = g;
		this->p = vt<vt<int> > (n, vt<int> (n, -1));
	}

	vt<vt<int> > build() {
		int n = g.size();

		for (int k = 0; k < n; k++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (i == j) continue;
					int edge = g[i][k] + g[k][j];
					if (g[i][j] > edge) {
						g[i][j] = edge;
						p[i][j] = k;
					}
				}
			}
		}

		return g;
	}

	void get_path(int i, int j, vt<int> & path) {
		if (p[i][j] == -1) {
			path.push_back(j);
			return;
		}
		get_path(i, p[i][j], path);
		get_path(p[i][j], j, path);
	}

	vt<int> get_path(int i, int j) {
		vt<int> path = {i};
		get_path(i, j, path);

		return path;
	}
};

void solve() {
	int n; cin >> n;
	vt<vt<int> > g(n, vt<int> (n));
	read2(g);

	floyd f = floyd(g);
	f.build();
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solve();
	return 0;
}