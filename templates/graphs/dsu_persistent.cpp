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

struct dsu_persistent {
    vt<int> par, rank;
    vt<pair<int*, int>> hist;
    int components;

    dsu_persistent() {}

    dsu_persistent(int n) {
        this->par = vt<int> (n, -1);
        this->rank = vt<int> (n, 0);
        this->components = n;
    }

    int find(int u) {
        while (par[u] != -1) {
            u = par[u];
        }
        return u;
    }

    bool merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) {
            return false;
        }
        if (rank[u] > rank[v]) {
            hist.emplace_back(&par[v], par[v]);
            par[v] = u;
        } else if (rank[u] < rank[v]) {
            hist.emplace_back(&par[u], par[u]);
            par[u] = v;
        } else {
            hist.emplace_back(&par[u], par[u]);
            hist.emplace_back(&rank[v], rank[v]);
            par[u] = v;
            ++rank[v];
        }
        components++;
        return true;
    }

    void rollback(int back_to) {
        while ((int)hist.size() > back_to) {
            *hist.back().first = hist.back().second;
            hist.pop_back();
            components--;
        }
    }
};

void solve() {
    
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}