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

struct Calculator {
	int ans = 0;
	int l = 0, r = -1;

	Calculator() {}

	void add(int idx) {
		
	}

	void remove(int idx) {

	}

	void add_left() {
		l--;
		add(l);
	}

	void add_right() {
		r++;
		add(r);
	}

	void remove_left() {
		remove(l);
		l++;
	}

	void remove_right() {
		remove(r);
		r--;
	}

	int get_ans() {
		return ans;
	}
};

struct MO {
	Calculator c;

	MO () {}

	MO (Calculator c) : c(c) {}

	struct Query {
		int l, r, idx;
		int64_t ord;

		Query(int l, int r, int idx) {
			this->l = l;
			this->r = r;
			this->idx = idx;
			this->ord = gilbert_order(l, r, 21, 0);
		}

		int64_t gilbert_order(int x, int y, int pow, int rotate) {
			if (pow == 0) return 0;
			int hpow = 1 << (pow-1);
			int seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : ((y < hpow) ? 1 : 2);
			seg = (seg + rotate) & 3;
			const int rotateDelta[4] = {3, 0, 0, 1};
			int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
			int nrot = (rotate + rotateDelta[seg]) & 3;
			int64_t subSquareSize = int64_t(1) << (2*pow - 2);
			int64_t ans = seg * subSquareSize;
			int64_t add = gilbert_order(nx, ny, pow-1, nrot);
			ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
			return ans;
		}

		bool operator<(Query other) const {
			return this->ord < other.ord;
		}
	};

	vt<int> solve(vt<Query> queries) {
		vt<int> answers(queries.size());
		sort(queries.begin(), queries.end());

		// invariant: data structure will always reflect the range [curL, curR]
		for (Query q : queries) {
			while (c.l > q.l) c.add_left();
			while (c.r < q.r) c.add_right();
			while (c.l < q.l) c.remove_left();
			while (c.r > q.r) c.remove_right();
			answers[q.idx] = c.get_ans();
		}

		return answers;
	}
};

void solve() {
	int q; cin >> q;
	
	Calculator c = Calculator();
	MO mo = MO(c);
	vt<MO::Query> queries;

	For(i, q) {
		int l, r; cin >> l >> r; l--, r--;
		queries.push_back(MO::Query{l, r, i});
	}

	vt<int> ans = mo.solve(queries);
	For(i, q) {
		cout << ans[i] << endl;
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solve();
	return 0;
}