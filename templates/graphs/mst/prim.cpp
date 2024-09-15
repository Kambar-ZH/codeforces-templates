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

struct node {
	int x, y;
	node() {};

	node(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

struct graph {
	vt<node> nodes;
	graph() {};

	graph(vt<node> nodes) {
		this->nodes = nodes;
	}

	ld dist(int i, int j) {
		int dx = nodes[i].x - nodes[j].x;
		int dy = nodes[i].y - nodes[j].y;
		return sqrt(dx * dx + dy * dy);
	}
};

struct prim {
	int n;
	graph gr;
	vt<pii> mst_edges;

	prim(int n, graph gr) {
		this->n = n;
		this->gr = gr;
	}

	ld get_mst() {
		vt<bool> used(n);
		vt<ld> min_edge(n, INF);
		vt<int> selected_edge(n, -1);
		min_edge[0] = 0;
		ld mst_cost = 0;

		for (int i = 0; i < n; i++) {
			int v = -1;
			for (int j=0; j<n; ++j) {
				if (!used[j] && (v == -1 || min_edge[j] < min_edge[v])) {
					v = j;
				}
			}

			if (min_edge[v] == MAX) {
				cout << "No MST!";
				exit(0);
			}

			used[v] = true;
			if (selected_edge[v] != -1) {
				mst_edges.emplace_back(v, selected_edge[v]);
				mst_cost += min_edge[v];
			}
		
			for (int to=0; to<n; ++to) {
				ld dist = gr.dist(v, to);
				if (dist < min_edge[to]) {
					min_edge[to] = dist;
					selected_edge[to] = v;
				}
			}
		}

		return mst_cost;
	}
};

void solve() {
	int n; cin >> n;
	vt<node> nodes;
	For(i, n) {
		int x, y; cin >> x >> y;
		nodes.push_back(node(x, y));
	}
	prim k = prim(n, graph(nodes));
	ld ans = k.get_mst();
	cout << ans << endl;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout << setprecision(20) << fixed;
	solve();
	return 0;
}