class DSU{
public:
    struct Node{
        int pred = -1;
        int sz = 1;
    };
    vector<Node> body;
    DSU(int siz) : body(siz) {}
    int FindPred(int i) {
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
        a = FindPred(a);
        b = FindPred(b);
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
    bool InOne(int a, int b) {
        return (FindPred(a) == FindPred(b));
    }
};

template <typename W>
vector<vector<pair<int, W>>> Kruskal(const vector<vector<pair<int, W>>>& gr) {
    int n = gr.size();
    vector<vector<pair<int, W>>> ans(n);
    DSU dsu(n);
    vector<pair<W, pair<int, int>>> s;
    for (int v = 0; v < n; ++v) {
        for (auto u : gr[v]) {
            s.push_back({u.second, {v, u.first}});
        }
    }
    sort(s.begin(), s.end());
    for (auto ed : s) {
        if (!dsu.InOne(ed.second.first, ed.second.second)) {
            ans[ed.second.first].push_back({ed.first, ed.second.second});
            ans[ed.second.second].push_back({ed.first, ed.second.first});
            dsu.Union(ed.second.first, ed.second.second);
        }
    }
    return ans;
}
