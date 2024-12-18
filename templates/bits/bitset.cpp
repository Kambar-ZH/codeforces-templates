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

struct Bitset {
	int base;
	int size;
	vt<int> base_power;

	Bitset(int base, int size) {
		this->base = base;
		this->size = size;
		this->precalc();
	}

	void precalc() {
		base_power = vt<int> (size + 1);
		base_power[0] = 1;
		for (int b = 1; b <= size; b++) {
			base_power[b] = base_power[b - 1] * base;
		}
	}

	int get_bit(int mask, int b) {
		return (mask / base_power[b]) % base;
	}

	int set_bit(int mask, int b, int v) {
		return mask + (v - get_bit(mask, b)) * base_power[b];
	}

	vt<vt<int> > get_mask_indexes_by_bit(int mask) {
		vt<vt<int> > bit_indexes(base);
		for (int b = 0; b < size; b++) {
			bit_indexes[get_bit(mask, b)].push_back(b);
		}
		return bit_indexes;
	}

	void print_mask(int mask) {
		for (int b = 0; b < size; b++) {
			cout << get_bit(mask, b) << " ";
		}
		cout << endl;
	}
};

void solve() {
    
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}