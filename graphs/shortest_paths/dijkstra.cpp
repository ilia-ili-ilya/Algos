const long long inf = 1e18;

vector<long long> dijkstra(const vector<vector<pair<int, int>>>& g, int start) {
    int n = g.size();
    vector<long long> dist(n, inf);
    set<pair<long long, int>> s;
    s.insert({0ll, start});
    while (!s.empty()) {
        pair<long long, int> p = *s.begin();
        s.erase(s.begin());
        if (dist[p.second] == inf) {
            dist[p.second] = p.first;
            for (auto z: g[p.second]) {
                if (dist[z.first] == inf)
                    s.insert({p.first + z.second, z.first});
            }
        }
    }
    return dist;
}
