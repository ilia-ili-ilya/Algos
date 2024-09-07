template <typename W>
vector<vector<pair<int, W>>> Prim(const vector<vector<pair<int, W>>>& gr) {
    int n = gr.size();
    vector<vector<pair<int, W>>> ans(n);
    vector<bool> used(n, false);
    set<pair<W, pair<int, int>>> s;
    used[0] = true;
    for (auto u : gr[0]) {
        s.insert({u.second, {0, u.first}});
    }
    while (!s.empty()) {
        pair<W, pair<int, int>> u = *s.begin();
        s.erase(s.begin());
        if (!used[u.second.second]) {
            ans[u.second.first].push_back({u.second.second, u.first});
            ans[u.second.second].push_back({u.second.first, u.first});
            used[u.second.second] = true;
            for (auto vv : gr[u.second.second]) {
                if (!used[vv.first]) {
                    s.insert({vv.second, {u.second.second, vv.first}});
                }
            }
        }
    }
    return ans;
}
