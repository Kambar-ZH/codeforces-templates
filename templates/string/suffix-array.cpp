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

struct suffix_array {
    const char last_symbol = '$';
    
    string s;
    int n;
    vt<int> suf_arr, eq_cls, lcp_arr;
    
    suffix_array(string s) {
        this->s = s + last_symbol;
        this->n = this->s.length();
        this->suf_arr.resize(n);
        this->eq_cls.resize(n);
        this->lcp_arr.resize(n);

        this->build_suf();
        this->build_lcp();
    }

    void count_sort() {
        vt<int> eq_cls_cnt(n);
        for (int i = 0; i < n; i++) {
            eq_cls_cnt[eq_cls[i]]++;
        }
        vt<int> bucket(n);
        for (int i = 1; i < n; i++) {
            bucket[i] = bucket[i - 1] + eq_cls_cnt[i - 1];
        }
        vt<int> new_suf_arr(n);
        for (int i = 0; i < n; i++) {
            int bucket_id = eq_cls[suf_arr[i]];
            new_suf_arr[bucket[bucket_id]] = suf_arr[i];
            bucket[bucket_id]++;
        }
        for (int i = 0; i < n; i++) {
            suf_arr[i] = new_suf_arr[i];
        }
    }

    void build_suf() {
        {
            vt<pair<char, int> > char_index;
            For(i, n) char_index.emplace_back(s[i], i);
            sort(all(char_index));
            For(i, n) suf_arr[i] = char_index[i].second;
            for (int i = 1; i < n; i++) {
                eq_cls[suf_arr[i]] = eq_cls[suf_arr[i - 1]];
                if (char_index[i].first != char_index[i - 1].first) {
                    eq_cls[suf_arr[i]] += 1;
                }
            }
        }
        
        for (int len = 1; len < n; len = 2 * len) {
            // suf_arr sorted by the second half, thus do offset to get the first half
            for (int i = 0; i < n; i++) {
                suf_arr[i] = suf_arr[i] - len;
                if (suf_arr[i] < 0) {
                    suf_arr[i] += n;
                }
            }

            // sort by the first half
            count_sort(); 

            vt<int> new_eq_class(n);
            new_eq_class[suf_arr[0]] = 0;

            // build new equivalence class
            pii prev = {eq_cls[suf_arr[0]], eq_cls[(suf_arr[0] + len) % n]};
            for (int i = 1; i < n; i++) {
                pii cur = {eq_cls[suf_arr[i]], eq_cls[(suf_arr[i] + len) % n]};
                new_eq_class[suf_arr[i]] = new_eq_class[suf_arr[i - 1]];
                if (prev != cur) {
                    new_eq_class[suf_arr[i]] += 1;
                }
                prev = cur;
            }

            eq_cls = new_eq_class;
        }
    }

    void build_lcp() {
        int lcp = 0;
        for (int suf = 0; suf < n - 1; suf++) {
            int suf_arr_i = eq_cls[suf];
            int suf_arr_j = suf_arr[suf_arr_i - 1];
            while (s[suf + lcp] == s[suf_arr_j + lcp]) lcp++;
            lcp_arr[suf_arr_i] = lcp;
            lcp = max(lcp - 1, 0);
        }
    }

    bool is_substr(const string &t) {
        int l = 0, r = s.size();
        while (l < r) {
            int m = (l + r) >> 1;
            bool less_or_equal = true;
            for (int i = 0; i < t.size(); i++) {
                if (t[i] < s[suf_arr[m] + i]) {
                    break;
                }
                if (suf_arr[m] + i > s.size() - 1 || t[i] > s[suf_arr[m] + i]) {
                    less_or_equal = false;
                    break;
                }
            }
            if (less_or_equal) {
                r = m;
            } else {
                l = m + 1;
            }
        }

        bool equal = true;
        for (int i = 0; i < t.size(); i++) {
            if (suf_arr[l] + i > s.size() - 1 || t[i] != s[suf_arr[l] + i]) {
                equal = false;
                break;
            }
        }
        return equal;
    }
};

void solve() {
    string s; cin >> s;
    suffix_array sa = suffix_array(s);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}