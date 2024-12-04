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
