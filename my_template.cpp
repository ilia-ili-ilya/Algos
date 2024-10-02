#include <bits/stdc++.h>

using namespace std;

//#pragma "O2"
#define int long long
#define ld long double
#define endl '\n'
#define fin for (int i = 0; i < n; ++i)
#define fim for (int i = 0; i < m; ++i)
#define fik for (int i = 0; i < k; ++i)
#define fjn for (int j = 0; j < n; ++j)
#define fjm for (int j = 0; j < m; ++j)
#define fjk for (int j = 0; j < k; ++j)
#define fji for (int j = 0; j < i; ++j)
#define pi pair<int, int>
#define vi vector<int>
#define mi map<int, int>
#define si set<int>
#define vb vector<bool>
#define vld vector<ld>
#define vpi vector<pi>
#define vvi vector<vi>
#define vvpi vector<vector<pi>>
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
#define print(a) for (auto _a : a) cout << _a << ' '; cout << endl
#define print1(a) for (auto _a : a) cout << _a+1 << ' '; cout << endl
#define printpi(a) cout << a.first << ' ' << a.second << endl
#define printvpi(a) for (auto _a : a) printpi(_a)
#define yes cout << "YES\n"
#define no cout << "NO\n"
#define alice cout << "Alice\n"
#define bob cout << "Bob\n"

const int mod = 1'000'000'007;
const int inf = 1000000000, INF = inf*inf;
mt19937 rnd(179);

int Bit(int mask, int b) { return (mask >> b) & 1; }
bool isin(auto a, auto x) {return (a.find(x) != a.end());}
int gcd(int a, int b) {if (a < b) swap(a, b);if (b == 0) return a;return gcd(b, a % b);}



void Solve(bool test = false) {

}


int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout.precision(20);
    int XXX = 1;
    cin >> XXX;
    while (XXX--) Solve();
}

