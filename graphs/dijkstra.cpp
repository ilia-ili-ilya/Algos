#include <iostream>
#include <vector>
#include <set>

#define int long long
const int inf = 1e18;
using namespace std;


vector<int> dijkstra(const vector<vector<pair<int, int>>>& g, int start) {
    int n = g.size();
    vector<int> dist(n, inf);
    set<pair<int, int>> s;
    s.insert({0, start});
    while (!s.empty()) {
        pair<int, int> p = *s.begin();
        s.erase(s.begin());
        if (dist[p.second] == inf) {
            dist[p.second] = p.first;
            for (auto z : g[p.second]) {
                if (dist[z.first] == inf)
                    s.insert({z.second + p.first, z.first});
            }
        }
    }
    return dist;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> a(n);
    for (int i = 0; i < m; ++i) {
        int x, y, v;
        cin >> x >> y >> v;
        a[x].push_back({y, v});
        a[y].push_back({x, v});
    }
    int s;
    cin >> s;
    vector<int> dist = dijkstra(a, s);
}
