#include <iostream>
#include <vector>
#define int long long

using namespace std;

const int inf = 1e18;

vector<int> ford_bellman(int n, const vector<pair<pair<int, int>, int>>& a, int start) {
    vector<int> dist(n, inf);
    dist[start] = 0;
    for (int i = 0; i < n; ++i) {
        for (auto aa : a) {
            dist[aa.first.second] = min(dist[aa.first.second], dist[aa.first.first] + aa.second);
        }
    }
    return dist;
}

int32_t main() {
    int n, m;
    cin >> n >> m;
    vector<pair<pair<int, int>, int>> a(m);
    for (int i = 0; i < m; ++i) {
        int x, y, v;
        cin >> x >> y >> v;
        --x; --y;
        a.push_back({{x, y}, v});
    }
    auto ans = ford_bellman(n, a, 0);
    for (auto aans : ans) {
        if (aans > inf / 2) cout << 30000 << ' ';
        else
        cout << aans << ' ';
    }
    cout << endl;
}
