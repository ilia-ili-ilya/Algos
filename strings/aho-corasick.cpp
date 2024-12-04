const int sigma = 'z' - 'a' + 1;

struct node {
    int to[sigma];
    bool term;
    node() : term(false) {
        for (int i = 0; i < sigma; ++i) {
            to[i] = -1;
        }
    }
};

class Bor {
protected:
    vector<node> bor;
public:
    Bor() : bor{node()} {}

    int GetSize() {
        return bor.size();
    }

    void AddWord(const string& s) {
        int i = 0;
        for (auto c : s) {
            if (bor[i].to[c - 'a'] == -1) {
                bor[i].to[c - 'a'] = bor.size();
                bor.push_back(node());
            }
            i = bor[i].to[c - 'a'];
        }
        bor[i].term = true;
    };

    bool FindWord(const string& s) {
        int i = 0;
        for (auto c : s) {
            if (bor[i].to[c - 'a'] == -1) {
                return false;
            }
            i = bor[i].to[c - 'a'];
        }
        return bor[i].term;
    }
};

class AhoBor : public Bor {
public:
    vector<int> link;
    vector<vector<int>> go;
    AhoBor() {}
    void MakeLinkGo() {
        int n = GetSize();
        link.clear();
        go.clear();
        link.resize(n);
        go.resize(n, vector<int>(sigma));
        link[0] = 0;
        for (int i = 0; i < sigma; ++i) {
            if (bor[0].to[i] != -1) {
                go[0][i] = bor[0].to[i];
            } else {
                go[0][i] = 0;
            }
        }
        deque<int> deq{0};
        while (!deq.empty()) {
            int z = deq.front();
            deq.pop_front();
            for (int i = 0; i < sigma; ++i) {
                if (bor[z].to[i] != -1) {
                    int u = bor[z].to[i];
                    if (z != 0) {
                        link[u] = go[link[z]][i];
                    } else {
                        link[u] = 0;
                    }
                    for (int j = 0; j < sigma; ++j) {
                        if (bor[u].to[j] != -1) {
                            go[u][j] = bor[u].to[j];
                        } else {
                            go[u][j] = go[link[u]][j];
                        }
                    }
                    deq.push_back(u);
                }
            }
        }
    }
};
