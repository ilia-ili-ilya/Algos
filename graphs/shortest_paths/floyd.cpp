vector<vector<long long>> Floyd(const vector<vector<pair<int, long long>>>& graph) {
    int n = graph.size();
    vector<vector<long long>> dist(n, vector<long long> (n));
    for (int v = 0; v < n; ++v) {
        for (auto u : graph[v]) {
            dist[v][u.first] = u.second;
        }
    }
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    return dist;
}
