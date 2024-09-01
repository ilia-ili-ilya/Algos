#include <bits/stdc++.h>

using namespace std;

template<typename T>
class DSU{
public:
    struct Node{
        int pred = -1;
        int sz = 1;
        T value;
        Node(T val) : value(val) {}
        Node(const T& val) : value(val) {}
        Node() : value(T()) {}
    };
    vector<Node> body;
    DSU(int siz) : body(siz) {}
    DSU(const vector<T>& values) : body(values.size()) {
        for (int i = 0; i < values.size(); ++i) {
            body[i].value = values[i];
        }
    }
    int Find_pred(int i) {
        int ii = i;
        while(body[i].pred != -1) {
            i = body[i].pred;
        }
        int root = i;
        while (body[ii].pred != -1) {
            i = ii;
            ii = body[i].pred;
            body[i].pred = root;
        }
        return root;
    }

    bool Union(int a, int b) {
        a = Find_pred(a);
        b = Find_pred(b);
        if (a == b) return false;
        if (body[a].sz >= body[b].sz) {
            body[a].sz += body[b].sz;
            body[b].pred = a;
        } else {
            body[b].sz += body[a].sz;
            body[a].pred = b;
        }
        return true;
    }
    bool in_one(int a, int b) {
        return (Find_pred(a) == Find_pred(b));
    }
};


