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

namespace TopSort {
	void dfs(int v, vt<bool> & visited, vt<int> & post_order, vt<vt<int> > & g) {
		visited[v] = true;
		for (int u : g[v]) {
			if (visited[u]) continue;
			dfs(u, visited, post_order, g);
		}
		post_order.push_back(v);
	}

	vt<int> top_sort(vt<vt<int> > & g) {
        int n = g.size();
		vt<int> post_order;
		vt<bool> visited(n);
		for (int v = 0; v < n; v++) {
			if (visited[v]) continue; 
			dfs(v, visited, post_order, g);
		}
        reverse(all(post_order));
        return post_order;
	}
}

struct Graph {
	int n, max_color;
	vt<int> vertex_color;
	vt<vt<int> > components_vertices;
	vt<vt<int> > condensated_g;
	vt<vt<int> > g, gr;

	Graph(int n, vt<pii> & edges) {
		this->max_color = 0;
		this->n = n;
		this->vertex_color = vt<int> (n, -1);
		this->build_graph(edges);
	};

	void build_graph(vt<pii> & edges) {
		g.resize(n);
		gr.resize(n);
		for (auto & [u, v] : edges) {
			g[u].push_back(v);
			gr[v].push_back(u);
		}
	}

	void condensate() {
		paint();
		condensated_g = vt<vt<int> > (max_color);
		components_vertices = vt<vt<int> > (max_color);
		for (int u = 0; u < n; u++) {
			int cu = vertex_color[u];
			components_vertices[cu].push_back(u);
			for (int v : g[u]) {
				int cv = vertex_color[v];
				if (cu == cv) continue;
				condensated_g[cu].push_back(cv);
			}
		}
	}

	void paint() {
		vt<int> post_order = TopSort::top_sort(g);
		vt<bool> visited(n);
		for (int v : post_order) {
			if (visited[v]) continue;
			paint(v, max_color++, visited);
		}
	}

	void paint(int v, int color, vt<bool> & visited) {
		visited[v] = true;
		vertex_color[v] = color;
		for (int u : gr[v]) {
			if (visited[u]) continue;
			paint(u, color, visited);
		}
	}
};

void solve() {
	int n, m; cin >> n >> m;
	vt<pii> edges;
	For(i, m) {
		int u, v; cin >> u >> v; u--, v--;
		edges.emplace_back(u, v);
	}
	Graph gr = Graph(n, edges);
	gr.condensate();
	
	print(gr.vertex_color);
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solve();
	return 0;
}