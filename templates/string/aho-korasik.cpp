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

const int N = 1e6, K = 26;

struct vertex {
	vt<int> next;
	vt<int> go;
	vt<int> leaf;
	int p;
	char pch;
	int link;
};

struct trie {
	vertex t[N+1];
	int ver_count;
	vt<string> strs;

	trie() {
		t[0].p = t[0].link = -1;
		t[0].next = vt<int> (K, -1);
		t[0].go = vt<int> (K, -1);
		ver_count = 1;
	}
	
	void add_string(const string & s) {
		int v = 0;
		for (size_t i=0; i<s.length(); ++i) {
			char c = s[i]-'a';
			if (t[v].next[c] == -1) {
				t[ver_count].next = vt<int> (K, -1);
				t[ver_count].go = vt<int> (K, -1);
				t[ver_count].link = -1;
				t[ver_count].p = v;
				t[ver_count].pch = c;
				t[v].next[c] = ver_count++;
			}
			v = t[v].next[c];
		}
		t[v].leaf.push_back(strs.size());
		strs.push_back(s);
	}
	
	int get_link(int v) {
		if (t[v].link == -1) {
			if (v == 0 || t[v].p == 0) {
				t[v].link = 0;
			} else {
				t[v].link = go(get_link(t[v].p), t[v].pch);
			}
		}
		return t[v].link;
	}
	
	int go(int v, char c) {
		if (t[v].go[c] == -1) {
			if (t[v].next[c] != -1) {
				t[v].go[c] = t[v].next[c];
			} else {
				t[v].go[c] = v == 0 ? 0 : go(get_link(v), c);
			}
		}
		return t[v].go[c];
	}

	vt<bool> exists(const string & s) {
		vt<int> visited(ver_count + 1);
		vt<bool> found(strs.size());
		int n = s.length();
		int cur = 0;
		for (int i = 0; i < n; i++) {
			cur = go(cur, s[i] - 'a');
			int tmp = cur;

			while (!visited[tmp]) {
				visited[tmp] = true;
                for (int x : t[tmp].leaf) {
                    found[x] = true;
                }
				tmp = get_link(tmp);
			}
		}
		return found;
	}

	vt<int> count(const string & s) {
		vt<bool> visited(ver_count + 1);
		vt<int> count(strs.size());
		int n = s.length();
		
		vt<vt<int> > gr(ver_count + 1);
		vt<int> factor(ver_count + 1);

		function<void(int)> calc = [&] (int v) {
			if (v == 0) {
				return;
			}
			if (visited[v]) {
				return;
			}
			visited[v] = true;
			int link = get_link(v);
			gr[link].push_back(v);
			calc(link);
		};

		int cur = 0;

		for (int i = 0; i < n; i++) {
			cur = go(cur, s[i] - 'a');
			factor[cur]++;
			calc(cur);
		}

		vt<int> cnt(ver_count + 1);
		function<int(int, int)> dp = [&] (int v, int f) -> int {
			if (cnt[v] != 0) {
				return cnt[v];
			}
			cnt[v] = factor[v];
			for (int u : gr[v]) {
				cnt[v] += dp(u, f + factor[v]);
			}
			for (int x : t[v].leaf) {
				count[x] += cnt[v];
			}
			return cnt[v];
		};

		dp(0, 0);

		return count;
	}

	vt<pii> first_and_last_occurence(const string & s) {
		vt<bool> visited(ver_count + 1);
		int n = s.length();
		
		vt<vt<int> > gr(ver_count + 1);
		vt<vt<int> > node(ver_count + 1);

		function<void(int)> calc = [&] (int v) {
			if (v == 0) {
				return;
			}
			if (visited[v]) {
				return;
			}
			visited[v] = true;
			int link = get_link(v);
			gr[link].push_back(v);
			calc(link);
		};

		int cur = 0;

		for (int i = 0; i < n; i++) {
			cur = go(cur, s[i] - 'a');
			node[cur].push_back(i);
			calc(cur);
		}

		vt<pii> ans(strs.size(), {-1, -1});
		function<pair<int, int>(int)> dp = [&] (int v) -> pair<int, int> {
            pii result = {-1, -1};
			for (int u : gr[v]) {
                auto ch = dp(u);
				if (ch.first != -1) {
					if (result.first == -1) {
						result.first = ch.first;
					} else {
						result.first = min(result.first, ch.first);
					}
				}
                result.second = max(result.second, ch.second);
			}
			
			for (int x : node[v]) {
                if (result.first == -1) {
                    result.first = x;
                } else {
				    result.first = min(result.first, x);
                }
				result.second = max(result.second, x);
			}

            if (result.first != -1) {
                for (int x : t[v].leaf) {
                    ans[x].first = result.first - (strs[x].length() - 1);
                    ans[x].second = result.second - (strs[x].length() - 1);
                }
            }

			return result;
		};

		dp(0);

		return ans;
	}
};

void solve() {
	int n; cin >> n;

	trie tr = trie();
	For(i, n) {
		string s; cin >> s;
		tr.add_string(s);
	}

	string t; cin >> t;
	vt<bool> ans = tr.exists(t);
	For(i, n) {
		cout << (ans[i] ? "Yes" : "No") << endl;
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solve();
	return 0;
}