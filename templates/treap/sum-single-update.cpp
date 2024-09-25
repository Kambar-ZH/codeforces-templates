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

mt19937 rnd;

struct Treap {
	int data;
	int priority;
	array<Treap*, 2> kids;
	int subtree_size;
	int sum;

	Treap(int data);
};

int size(Treap *me) {
	return me == nullptr ? 0 : me->subtree_size;
}

int sum(Treap *me) {
	return me == nullptr ? 0 : me->sum;
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

pair<int, int> lowerbound(Treap *me, int target) {
	if (me == nullptr) {
		return {0, 0};	
	}
	if (target <= sum(me->kids[0])) {
		return lowerbound(me->kids[0], target);
	}
	target -= (sum(me->kids[0]) + me->data);
    if (target <= 0) {
        return {sum(me->kids[0]) + me->data, size(me->kids[0]) + 1};
    }
	auto res = lowerbound(me->kids[1], target);
	return {res.first + sum(me->kids[0]) + me->data, res.second + size(me->kids[0]) + 1};
}

Treap* get_by_id(Treap *me, int id) {
	if (me == nullptr) {
		return nullptr;	
	}
	if (id <= size(me->kids[0])) {
		return get_by_id(me->kids[0], id);
	}
	id -= size(me->kids[0]) + 1;
    if (id == 0) {
        return me;
    }
	auto res = get_by_id(me->kids[1], id);
	return res;
}

Treap *update(Treap *t, int l, int x) {
    auto [left, other] = split(t, l-1);
    auto [mid, right] = split(other, 1);
    mid->data = x;
	// CAUTION: need to recalc after data modification
    recalc(mid);
    return merge(merge(left, mid), right);
}

Treap *add(Treap *t, int l, int x) {
    auto [left, other] = split(t, l-1);
    auto [mid, right] = split(other, 1);
    mid->data += x;
	// CAUTION: need to recalc after data modification
    recalc(mid);
    return merge(merge(left, mid), right);
}

Treap::Treap(int data) {
	kids={nullptr, nullptr};
	this->data = data;
	this->priority = rnd();
	this->subtree_size = 1;
	this->sum = data;
	recalc(this);
}

template<class F> 
void each(Treap *n, F f) {
	if (n) { each(n->kids[0], f); f(n); each(n->kids[1], f); }
}

void solve() {
    
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}