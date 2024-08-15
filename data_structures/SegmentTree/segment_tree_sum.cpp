#include <bits/stdc++.h>

using namespace std;

#define int long long
#define endl '\n'

class SegmentTree {
private:
    int sz;
    vector<int> body;
public:
    SegmentTree(int n) {
        sz = (2 << (int)log2(n - 1));
        body.resize(sz * 2 - 1, 0);
    }

    SegmentTree(vector<int> a) {
        sz = (2 << (int)log2(a.size() - 1));
        body.resize(sz * 2 - 1);
        for (int i = a.size(); i < sz; ++i) {
            a.push_back(0);
        }
        Build(a, 0, 0, sz);
    }
    int n() {
        return sz;
    }

private:
    void Build(const vector<int>& a, int i, int l, int r) {
        if (r - l == 1) {
            body[i] = a[i - sz + 1];
        } else {
            int m = (r + l) / 2;
            Build(a, i + i + 1, l, m);
            Build(a, i + i + 2, m, r);
            body[i] = body[i + i + 1] + body[i + i + 2];
        }
    }
public:
    int Sum(int i, int l, int r, int L, int R) {
        if ((L >= r) || (R <= l)) return 0;
        if ((l >= L) && (r <= R)) return body[i];
        int m = (r + l) / 2;
        return Sum(i + i + 1, l, m, L, R) + Sum(i + i + 2, m, r, L, R);
    }

    void Change(int i, int l, int r, int ind, int val) {
        if (r - l == 1) {
            body[i] = val;
        } else {
            int m = (l + r) >> 1;
            if (ind < m) {
                Change(i + i + 1, l, m, ind, val);
            } else {
                Change(i + i + 2, m, r, ind, val);
            }
            body[i] = body[i + i + 1] + body[i + i + 2];
        }
    }
    int F_sum(int l, int r) {
        int su = 0;
        while (l < r) {
            if (!(l & 1)) su += body[l];
            if (r & 1) su += body[r];
            l >>= 1;
            r >>= 1;
            r--;
        }
        if (l == r) su += body[l];
        return su;
    }
};

void Solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    SegmentTree tre(a);
    while (q--) {
        int a1, a2, a3;
        cin >> a1 >> a2 >> a3;
        if (a1 == 1) {
            tre.Change(0, 0, tre.n(), a2, a3);
        } else {
            cout << tre.F_sum(a2 + tre.n() - 1, a3 + tre.n() - 2) << endl;
        }
    }
}


int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int X = 1;
    //cin >> X;
    while (X--) Solve();
}
