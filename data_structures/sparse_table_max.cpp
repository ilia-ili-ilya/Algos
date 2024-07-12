#include <bits/stdc++.h>

using namespace std;


class SparseTable{
private:
    const int sz;
    const int lag;
    int* body;
public:
    SparseTable(const vector<int>& a) : sz(a.size()), lag(__lg(a.size())+1), body(new int[sz*lag]){
        //body[i*lag+j]
        for (int i = 0; i < sz; ++i) {
            body[i*lag] = a[i];
        }
        for (int pw = 1; pw < lag; ++pw) {
            for (int i = 0; i < sz - (1 << pw) + 1; ++i) {
                body[i*lag+pw] = max(body[i*lag+pw-1], body[(i+(1<<(pw-1)))*lag+pw-1]);
            }
        }
    }
    ~SparseTable() {
        delete[] body;
    }
    int Max(int l, int r) { // [l, r)
        int ln = __lg(r-l);
        return max(body[l*lag+ln], body[(r-(1<<ln)) * lag + ln]);
    }
    void print() {
        for (int pw = 0; pw < lag; ++pw) {
            for (int i = 0; i < sz - (1 << pw) + 1; ++i) {
                cout << body[i*lag + pw] << ' ';
            }
            cout << endl;
        }
    }
};


