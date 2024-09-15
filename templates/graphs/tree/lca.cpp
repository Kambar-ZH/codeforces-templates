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

struct Node {
	ll value;
	Node() : value(MAX) {};

	Node(ll value) : value(value) {};

	static Node merge(Node & n1, Node & n2) {
		Node r(min(n1.value, n2.value));
		return r;
	}
};

template<typename T>
struct LcaTree {
	int N, L;
	vt<int> par, depth;
	vt<T> val;
	vt<vt<int> > dp_par; // dp_par[0] is itself 
	vt<vt<T> > dp_val;
	int timer;
	vt<int> in, out;

	LcaTree() {}

	LcaTree(int N) {
		this->N      = N;
		this->L      = log2(N) + 2;
		this->par    = vt<int> (N, -1);
		this->val    = vt<T> (N);
		this->depth  = vt<int> (N);
		this->in     = vt<int> (N);
		this->out    = vt<int> (N);
		this->timer  = 0;
	}

	LcaTree(vt<T> val) {
		this->N      = val.size();
		this->L      = log2(N) + 2;
		this->par    = vt<int> (N, -1);
		this->val    = val;
		this->depth  = vt<int> (N);
		this->in     = vt<int> (N);
		this->out    = vt<int> (N);
		this->timer  = 0;
	}

	void dfs(int v, int p, vt<vt<int> > & g) {
		in[v] = ++timer;
		par[v] = p;
		if (p != -1) {
			depth[v] = depth[p] + 1;
		}

		for (int u : g[v]) {
			if (u == p) continue;
			dfs(u, v, g);
		}

		out[v] = timer;
	}

	void calc_dp_par() {
		dp_par = vt<vt<int> >(N, vt<int> (L, -1));

		for (int i = 0; i < N; i++) {
			dp_par[i][0] = i;
			dp_par[i][1] = par[i];
		}

		for (int l = 2; l < L; l++) {
			for (int i = 0; i < N; i++) {
				int par = dp_par[i][l - 1];
				if (par != -1) {
					dp_par[i][l] = dp_par[par][l - 1];
				}
			}
		}
	}

	void calc_dp_val() {
		dp_val = vt<vt<T> >(N, vt<T> (L));

		for (int i = 0; i < N; i++) {
			dp_val[i][0] = val[i];
			dp_val[i][1] = val[i];
			if (par[i] != -1) {
				dp_val[i][1] = T::merge(dp_val[i][1], val[par[i]]);
			}
		}

		for (int l = 2; l < L; l++) {
			for (int i = 0; i < N; i++) {
				int par = dp_par[i][l - 1];
				if (par != -1) {
					dp_val[i][l] = T::merge(dp_val[i][l - 1], dp_val[par][l - 1]);
				}
			}
		}
	}

	bool is_par(int v, int p) {
		return in[p] <= in[v] && out[v] <= out[p];
	}

	int lca(int node1, int node2) {
		if (is_par(node2, node1)) {
			return node1;
		}

		if (is_par(node1, node2)) {
			return node2;
		}

		for (int i = L - 1; i >= 1; i--) {
			int par = dp_par[node1][i];
			if (par == -1) continue;
			if (!is_par(node2, par)) {
				node1 = par;
			}
		}

		return par[node1];
	}

	// returns -1 if k-th parent doesn't exist 
	int kth_par(int node, int k) {
		if (k >= N) {
			return -1;
		}

		for (int i = L - 1; i >= 1; i--) {
			int par = dp_par[node][i];
			if (k & (1 << (i - 1))) {
				k ^= (1 << (i - 1));
				node = par;
				if (node == -1) {
					return -1;
				}
			}
		}

		return node;
	}

	T ans(int node, int k) {
		if (k < 0) {
			return T();
		}
		T val = T();

		for (int i = L - 1; i >= 1; i--) {
			int par = dp_par[node][i];
			if (par == -1) continue;
			if (k & (1 << (i - 1))) {
				k ^= (1 << (i - 1));
				val = T::merge(val, dp_val[node][i]);
				node = par;
			}
		}

		return T::merge(val, dp_val[node][0]);
	}

	// to simulate edge - set value of directed edge (u -> v) to v-th node
	T ans_between_edges(int node1, int node2) {
		int p = lca(node1, node2);
		T ans1 = ans(node1, depth[node1] - depth[p] - 1),
		  ans2 = ans(node2, depth[node2] - depth[p] - 1);

		return T::merge(ans1, ans2);
	}

	T ans_between_nodes(int node1, int node2) {
		int p = lca(node1, node2);
		T ans1 = ans(node1, depth[node1] - depth[p]),
		  ans2 = ans(node2, depth[node2] - depth[p]);

		return T::merge(ans1, ans2);
	}
};

void solve() {
	int n; cin >> n;
	vt<vt<int> > g(n);
	vt<Node> val(n);
	For(i, n - 1) {
		int x, y; cin >> x >> y; x--;
		g[x].push_back(i + 1);
		val[i + 1] = Node(y);
	}
	auto t = LcaTree<Node>(val);
	t.dfs(0, -1, g);
	t.calc_dp_par();
	t.calc_dp_val();
	int m; cin >> m;
	For(i, m) {
		int u, v; cin >> u >> v; u--, v--;
		cout << t.ans_between_edges(u, v).value << endl;
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solve();
	return 0;
}