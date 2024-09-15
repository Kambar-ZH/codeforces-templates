#include <bits/stdc++.h>

using namespace std;

#define For(i, n)           for(int i = 0; i < n; ++i)
#define qFor(i, x, n)       for(int i = x; i < n; ++i)
#define all(x)              (x).begin(),(x).end()
#define rall(x)             (x).rbegin(),(x).rend()

#define ld                  long double
#define pii                 pair<int, int>
#define vt                  vector
#define ll                  long long
#define endl                '\n'

#define DEBUG
#ifdef DEBUG
#define dout(str)           do {cout << "! " << str << endl;} while(false)
#else
#define dout(str)           do { } while ( false )
#endif

const int MAX = 1e9;
const int MOD = 1e9 + 7;
const ll  INF = 1e18;
const ld  PI  = 3.14159265358979323846;
 
template<typename T>
void read(vt<T> & a) {
	For(i, a.size()) cin >> a[i];
}
template<typename T>
void print(vt<T> & a) {
	For(i, a.size()) cout << a[i] << " ";
	cout << endl;
}
template<typename T>
void print2(vt<vt<T> > & a) {
	For(i, a.size()) {
		For(j, a[i].size()) cout << a[i][j] << " ";
		cout << endl;
	}
}
template<typename T>
void read2(vt<vt<T> > & a) {
	For(i, a.size()) For(j, a[i].size()) cin >> a[i][j];
}

struct point {
	int x, y;
	point() {}
	point(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

ld triangle_area(point & a, point & b) {
	return a.x * b.y - b.x * a.y;
}

ld mod(point & a) {
	return sqrt(a.x * a.x + a.y * a.y);
}

void solve()
{
	vt<point> pts;
	int n = 2;
	For(i, n) {
		int x, y; cin >> x >> y;
		pts.push_back(point(x, y));
	}
	pts[1].x -= pts[0].x;
	pts[1].y -= pts[0].y;
	cout << mod(pts[1]) << endl;
}
 
int main() 
{
#define FILE
#ifdef FILE
	freopen("length.out", "w", stdout);
	freopen("length.in", "r", stdin);
#endif
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout << setprecision(10) << fixed;
	int T = 1;
	For(t, T) {
		solve();
	}
	return 0;
}