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

template<typename T>
void read(vt<T> & a) {For(i, a.size()) cin >> a[i];}
template<typename T>
void read2(vt<vt<T> > & a) {For(i, a.size()) read(a[i]);}
template<typename T>
void print(vt<T> & a) {For(i, a.size()) cout << a[i] << " "; cout << endl;}
template<typename T>
void print2(vt<vt<T> > & a) {For(i, a.size()) print(a[i]);}

const int MAX = 1e9;
const int MOD = 1e9+7;
const ll  INF = 1e18;
const ld  PI  = 3.14159265358979323846;

struct static_mex {
    int N;
    vt<bool> used;

    static_mex() {}
    
    static_mex(int N) {
        this->N = N;
        this->used.assign(N + 1, false);
    }

    int mex(const vector<int> & a) {
        int n = a.size();
        for (int i = 0; i < n; i++) {
            if (a[i] <= N) {
                used[a[i]] = true;
            }
        }
        int result = -1;
        for (int i = 0; ; i++) {
            if (!used[i]) {
                result = i;
                break;
            }
        }
        for (int i = 0 ; i < n; i++) {
            if (a[i] <= N) {
                used[a[i]] = false;
            }
        }
        return result;
    }
};

struct grundy {
	const int N = 100;
    static_mex m;
	vt<int> g;

	grundy() {
		this->g.assign(N + 1, -1);
		this->m = static_mex(N);
	}

	int _calc(int n) {
		if (n <= 0) {
			return 0;
		}
		if (g[n] != -1) {
			return g[n];
		}
		vt<int> a;

		a.push_back(calc(n - 2));
		for (int i = 2; i <= n - 1; i++) {
			int XOR = calc(i - 2) ^ calc(n - 1 - i);
            a.push_back(XOR);
		}

		return g[n] = m.mex(a);
	}

	int calc(int n) {
		if (n >= 52) {
			n = (n - 52) % 34 + 52;
		}
		return _calc(n);
	}
};

void solve() {
	int n; cin >> n;
	grundy g = grundy();
	if (g.calc(n) == 0) {
		cout << "Black" << endl; 
	} else {
		cout << "White" << endl;
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solve();
	return 0;
}