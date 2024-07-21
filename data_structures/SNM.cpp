#include <bits/stdc++.h>

using namespace std;

class SNM{
public:
    struct Node{
        int pred = -1;
        int sz = 1;
        int value;
        Node(int val) : value(val) {}
        Node() : value(0) {}
    };
    vector<Node> body;
    SNM(int siz) : body(siz) {}
    SNM(vector<int> values) : body(values.size()) {
        for (int i = 0; i < values.size(); ++i) {
            body[i].value = values[i];
        }
    }
    int find_pred(int i) {
        while(body[i].pred != -1) {
           i = body[i].pred;
        }
        return i;
    }
    bool merge(int a, int b) {
        a = find_pred(a);
        b = find_pred(b);
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
        return (find_pred(a) == find_pred(b));
    }
};


