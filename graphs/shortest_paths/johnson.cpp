namespace Johnson {
    const long long inf = 1e18;
    bool has_cycle = false;
    vector<long long> dijkstra(const vector<vector<pair<int, long long>>>& g, int start) {
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


    vector<long long> ford_bellman(const vector<vector<pair<int, long long>>>& graph, int start) {
        int n = graph.size();
        vector<pair<pair<int, int>, long long>> a;
        for (int v = 0; v < n; ++v) {
            for (auto u : graph[v]) {
                a.push_back({{v, u.first}, u.second});
            }
        }
        vector<long long> dist(n, inf);
        dist[start] = 0;
        int i = 0;
        bool tr = true;
        while (tr) {
            tr = false;
            for (auto aa : a) {
                if (dist[aa.first.second] > dist[aa.first.first] + aa.second) {
                    dist[aa.first.second] = dist[aa.first.first] + aa.second;
                    tr = true;
                }
            }
            ++i;
            if (i == n) {
                has_cycle = true;
                return dist;
            }
        }
        return dist;
    }

    vector<vector<long long>> johnson(vector<vector<pair<int, long long>>> graph) {
        has_cycle = false;
        int n = graph.size();
        graph.push_back(vector<pair<int, long long>> (n, {0, 0}));
        for (int i = 0; i < n; ++i) {
            graph[n][i].first = i;
        }
        vector<long long> potential = ford_bellman(graph, n);
        potential.pop_back();
        graph.pop_back();
        for (int v = 0; v < n; ++v) {
            for (auto& u : graph[v]) {
                u.second += potential[v];
                u.second -= potential[u.first];
            }
        }
        vector<vector<long long>> dists(n);
        for (int st = 0; st < n; ++st) {
            dists[st] = dijkstra(graph, st);
            for (int v = 0; v < n; ++v) {
                dists[st][v] += potential[v] - potential[st];
            }
        }
        return dists;
    }
}

