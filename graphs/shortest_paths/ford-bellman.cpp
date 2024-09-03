const int inf = 1e18;

vector<long long> ford_bellman(int n, const vector<pair<pair<int, int>, long long>>& a, int start) {
    vector<long long> dist(n, inf);
    dist[start] = 0;
    for (int i = 0; i < n; ++i) {
        for (auto aa : a) {
            dist[aa.first.second] = min(dist[aa.first.second], dist[aa.first.first] + aa.second);
        }
    }
    return dist;
}
