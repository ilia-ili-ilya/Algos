#include <bits/stdc++.h>

using namespace std;
template <typename Val>
class SegmentTree {
private:
    struct Node {
        Val val;
        Val cash = 0;
    };

    int sz;
    vector<Node> body;
    Node Unite(Node a, Node b) {
        return Node(a.val + b.val);
    }

    void Push(int ind) {
        body[ind].val += body[ind].cash;
        if (ind < sz-1) {
            body[L(ind)].cash += body[ind].cash;
            body[R(ind)].cash += body[ind].cash;
        }
        body[ind].cash = 0;
    }

    inline int L(int ind) {
        return ind + ind + 1;
    }

    inline int R(int ind) {
        return ind + ind + 2;
    }

    void _BuildTree(int i, int l, int r) {
        if (r-l == 1) return;
        int mid = (r+l) / 2;
        _BuildTree(L(i), l, mid);
        _BuildTree(R(i), mid, r);
        body[i] = Unite(body[L(i)], body[R(i)]);
    }

    void _ChangeNode(int i, int l, int r, int ind, Val val) {
        Push(i);
        if (r-l == 1) {
            body[i] = Node(val);
            return;
        }
        int mid = (r + l) / 2;
        if (ind < mid) {
            _ChangeNode(L(i), l, mid, ind, val);
        } else {
            _ChangeNode(R(i), mid, r, ind, val);
        }
        body[i] = Unite(body[L(i)], body[R(i)]);
    }

    void _AddForSegment(int i, int l, int r, int ll, int rr, Val val) {
        if ((ll <= l) && (rr >= r)) {
            body[i].cash += val;
            return;
        }
        if ((ll >= r) || (l >= rr)) return;
        int mid = (r + l) / 2;
        _AddForSegment(L(i), l, mid, ll, rr, val);
        _AddForSegment(R(i), mid, r, ll, rr, val);
    }

    Node _OperationOnSegment(int i, int l, int r, int ll, int rr) {
        Push(i);
        if ((ll <= l) && (rr >= r)) return body[i];
        if ((ll >= r) || (l >= rr)) return Node();
        int mid = (r + l) / 2;
        return Unite(_OperationOnSegment(L(i), l, mid, ll, rr),
                     _OperationOnSegment(R(i), mid, r, ll, rr));
    }
public:
    SegmentTree(int n) {
        sz = 1 << (__lg(n-1) + 1);
        body.resize(2*sz-1, Node());
    }

    SegmentTree(vector<Val> a) {
        sz = 1 << (__lg(a.size() - 1) + 1);
        body.resize(2*sz-1, Node());
        for (int i = sz - 1; i < sz - 1 + a.size(); ++i) {
            body[i] = Node(a[i-sz+1]);
        }
        _BuildTree(0, 0, sz);
    }
    
    void ChangeNode(int ind, Val val) {
        _ChangeNode(0, 0, sz, ind, val);
    }

    void ChangeSegment(int l, int r, Val val) {
        _AddForSegment(0, 0, sz, l, r, val);
    }

    Val OperationOnSegment(int l, int r) {
        return _OperationOnSegment(0, 0, sz, l, r).val;
    }

    Val ValOfOne(int ind) {
        return _OperationOnSegment(0, 0, sz, ind, ind+1).val;
    }
    
};

int main() {
}
