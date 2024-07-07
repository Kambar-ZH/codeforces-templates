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

#define sim template < class c
#define ris return * this
#define dor > debug & operator <<
#define eni(x) sim > typename \
enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge { c b, e; };
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0);
sim > char dud(...);
#define LOCAL
struct debug {
#ifdef LOCAL
~debug() { cerr << endl; }
eni(!=) cerr << boolalpha << i; ris; }
eni(==) ris << range(begin(i), end(i)); }
sim, class b dor(pair < b, c > d) {
ris << "(" << d.first << ", " << d.second << ")";
}
sim dor(rge<c> d) {
*this << "[";
for (auto it = d.b; it != d.e; ++it)
	*this << ", " + 2 * (it == d.b) << *it;
ris << "]";
}
#else
sim dor(const c&) { ris; }
#endif
};
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "

template<typename T> void read(vt<T> & a) {For(i, a.size()) cin >> a[i];}
template<typename T> void read2(vt<vt<T> > & a) {For(i, a.size()) read(a[i]);}
template<typename T> void print(vt<T> & a) {For(i, a.size()) cout << a[i] << " "; cout << endl;}
template<typename T> void print2(vt<vt<T> > & a) {For(i, a.size()) print(a[i]);}

const int MAX = 1e9;
const int MOD = 1000000007;
const ll  INF = 1e18;
const ld  PI  = 3.14159265358979323846;

mt19937 rnd;

struct Treap {
	int data;
	int priority;
	array<Treap*, 2> kids;
	int subtree_size;

	Treap(int data);
};

int size(Treap *me) {
	return me == nullptr ? 0 : me->subtree_size;
}

void recalc(Treap *me) {
	if (me==nullptr) return;
	me->subtree_size = 1;
	for (Treap* t:me->kids) if (t != nullptr) {
		me->subtree_size += t->subtree_size;
	}
}

Treap* merge(Treap *l, Treap *r) {
	if (l==nullptr) return r;
	if (r==nullptr) return l;
	if (l->priority < r->priority) {
		l->kids[1]=merge(l->kids[1], r);
		recalc(l);
		return l;
	}
	else {
		r->kids[0]=merge(l, r->kids[0]);
		recalc(r);
		return r;
	}
}

array<Treap*, 2> split(Treap *me, int n_in_left) {
	if (me == nullptr) return {nullptr, nullptr};
	if (size(me->kids[0])>=n_in_left) {
		array<Treap*, 2> left_res=split(me->kids[0], n_in_left);
		me->kids[0]=left_res[1];
		recalc(me);
		return {left_res[0], me};
	}
	else {
		n_in_left = n_in_left - size(me->kids[0]) - 1;
		array<Treap*, 2> right_res = split(me->kids[1], n_in_left);
		me->kids[1] = right_res[0];
		recalc(me);
		return {me, right_res[1]};
	}
	return {nullptr, nullptr};
}

pair<int, bool> get_in_left(Treap *me, int target) {
	if (me == nullptr) {
		return pair(0, false);	
	}
	if (me->data == target) {
		return pair(size(me->kids[0]), true);
	}
	if (target < me->data) {
		return get_in_left(me->kids[0], target);
	}
	auto res = get_in_left(me->kids[1], target);
	return pair(res.first + size(me->kids[0]) + 1, res.second);
}

Treap::Treap(int data) {
	kids={nullptr, nullptr};
	this->data = data;
	this->priority = rnd();
	this->subtree_size = 1;
	recalc(this);
}

template<class F> 
void each(Treap *n, F f) {
	if (n) { each(n->kids[0], f); f(n); each(n->kids[1], f); }
}

// https://coderun.yandex.ru/selections/backend/problems/lollipops/description?currentPage=1&pageSize=20

void solve() {
	int n, m, q; cin >> n >> m >> q;
	vt<Treap*> servers(m);
	vt<int> p(n); read(p);
	For(i, n) p[i]--;
	for (int i = 0; i < n; i++) {
		auto t = new Treap(i);
		servers[p[i]] = merge(servers[p[i]], t);
	}
	for (int j = 0; j < q; j++) {
		int a, b, l, r; cin >> a >> b >> l >> r; a--, b--, l--, r--;
		auto in_left_of_l = get_in_left(servers[a], l);
		auto in_left_of_r = get_in_left(servers[a], r);
		if (!in_left_of_l.second || !in_left_of_r.second || in_left_of_r.first - in_left_of_l.first != r - l) {
			cout << 0 << endl;
			continue;
		}
		auto [other, third_a] = split(servers[a], in_left_of_r.first + 1);
		auto [first_a, second_a] = split(other, in_left_of_l.first);
		servers[a] = merge(first_a, third_a);
		in_left_of_l = get_in_left(servers[b], l);
		auto [first_b, second_b] = split(servers[b], in_left_of_l.first);
		servers[b] = merge(first_b, merge(second_a, second_b));
		cout << 1 << endl;
	}
}

// THE SOLUTION IS ALWAYS SIMPLE
// THE CODE IS ALWAYS SHORT

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef DEBUG
	freopen("output.txt", "w", stdout);
	freopen("input.txt", "r", stdin);
#endif
	int T = 1;
	For(t, T) solve();
	return 0;
}