#include <bits/stdc++.h>


using namespace std;

typedef long double ld;
typedef long long ll;
typedef complex<long double> cld;

const ld PI = acosl(-1);
const int N = (1 << 20);
const int mod = 998244353;

ll Pow(ll val, int x) {
    if (x == 0) return 1;
    if (x % 2 == 0) {
        return Pow((val * val) % mod, x / 2);
    }
    return (val * Pow(val, x - 1)) % mod;
}

int reverseBits(int x, int n) {
    int ans = 0;
    for (; n > 1; n >>= 1) {
        ans = ans * 2 + (x&1);
        x >>= 1;
    }
    return ans;
}

void fft(ll* a, int n, ll* wNdegs) {
    if (n == 1) return;
    for (int i = 0; i < n; ++i) {
        int revi = reverseBits(i, n);
        if (i < revi) {
            swap(a[i], a[revi]);
        }
    }
    ll* aend = a + n;
    for (int l = 2; l <= n; l *= 2) {
        int lNn = (n / l) *(N/n);
        for (ll* st = a; st != aend; st += l) {
            ll* wldeg = wNdegs;

            ll* ukr = st + l/2;
            ll* stend = st + l;
            ll* ukl = st;
            for (; ukr != stend; ++ukl, ++ukr) {
                ll u = *ukl;
                ll v = ((*wldeg) * (*ukr)) % mod;
                *ukl = (u + v) % mod;
                *ukr = (u - v + mod) % mod;
                wldeg += lNn;
            }
        }
    }
}

void fftInverse(ll* a, int n, ll* wNdegs) {
    ll dn = Pow(n, mod - 2);
    if (n == 1)
        return;
    fft(a, n, wNdegs);
    reverse(a + 1, a + n);
    for (int i = 0; i < n; ++i) {
        a[i] *= dn;
        a[i] %= mod;
    }
}

ll* makeNice(vector<long long> a, int n) {
    ll* ans = new ll[n];
    for (int i = 0; i < a.size(); ++i) {
        ans[i] = a[i];
    }
    for (int i = a.size(); i < n; ++i) {
        ans[i] = 0;
    }
    return ans;
}

ll* calcwNdegs() {
    ll* wNdegs = new ll[N];
    ll root = Pow(3, 119*8);
    wNdegs[0] = 1;
    for (int i = 1; i < N; ++i) {
        wNdegs[i] = (wNdegs[i - 1] * root) % mod;
    }
    return wNdegs;
}

vector<ll> multipy(const vector<ll>& a, const vector<ll>& b, ll* wNdegs) {
    int n = 1;
    while (n < max(a.size(), b.size())) {
        n *= 2;
    }
    ll* ca = makeNice(a, 2*n);
    ll* cb = makeNice(b, 2*n);
    fft(ca, 2*n, wNdegs);
    fft(cb, 2*n, wNdegs);
    ll cc[2*n];
    for (int i = 0; i < 2*n; ++i) {
        cc[i] = ca[i] * cb[i];
    }
    vector<ll> c(2*n);
    fftInverse(cc, 2*n, wNdegs);
    for (int i = 0; i < 2*n; ++i) {
        c[i] = cc[i];
    }
    return c;

}

int main() {
    ll* wNdegs = calcwNdegs();
    vector<ll> a{mod - 1}, b{mod - 1};
    vector<ll> c = multipy(a, b, wNdegs);
    for (auto cc : c) cout << cc << ' '; cout << endl;
}

