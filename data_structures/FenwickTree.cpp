#include <bits/stdc++.h>

using namespace std;


class FenwickTree {
private:
    int* t;
    int sz;
public:
    FenwickTree(int n) : t(new int[n+1]), sz(n) {}
    FenwickTree(const vector<int>& a) : t(new int[a.size() + 1]), sz(a.size()) {
        for (int i = 1; i <= a.size(); ++i) {
            Add(i, a[i-1]);
        }
    }
    int __sum (int r) {
        int res = 0;
        for (; r > 0; r -= r & -r)
            res += t[r];
        return res;
    }

    int Sum (int l, int r) {  // в 1-индексации, обе границы вклиючены 
        return __sum(r) - __sum(l-1);
    }

    void Add (int k, int x) {  // в 1-индексации
        for (; k <= sz; k += k & -k)
            t[k] += x;
    }

};






int32_t main() {
    FenwickTree s({1, 2, 3});
    cout << s.Sum(1, 2) << endl; // 3
    s.Add(3, 10);
    cout << s.Sum(1, 3) << endl; // 16
}
