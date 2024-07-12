#include <bits/stdc++.h>


using namespace std;

typedef long double ld;
typedef complex<long double> cld;

const ld PI = acosl(-1);
const int N = (1 << 20);

int reverseBits(int x, int n) {
    int ans = 0;
    for (; n > 1; n >>= 1) {
        ans = ans * 2 + (x&1);
        x >>= 1;
    }
    return ans;
}

void fft(cld* a, int n, cld* wNdegs) {
    if (n == 1) return;
    for (int i = 0; i < n; ++i) {
        int revi = reverseBits(i, n);
        if (i < revi) {
            swap(a[i], a[revi]);
        }
    }
    cld* aend = a + n;
    for (int l = 2; l <= n; l *= 2) {
        int lNn = (n / l) *(N/n);
        for (cld* st = a; st != aend; st += l) {
            cld* wldeg = wNdegs;

            cld* ukr = st + l/2;
            cld* stend = st + l;
            cld* ukl = st;
            for (; ukr != stend; ++ukl, ++ukr) {
                cld u = *ukl;
                cld v = (*wldeg) * (*ukr);
                *ukl = u + v;
                *ukr = u - v;
                wldeg += lNn;
            }
        }
    }
}

void fftInverse(cld* a, int n, cld* wNdegs) {
    if (n == 1)
        return;
    fft(a, n, wNdegs);
    reverse(a + 1, a + n);
    for (int i = 0; i < n; ++i) {
        a[i] /= n;
    }
}

cld* makeComplex(vector<long long> a, int n) {
    cld* ans = new cld[n];
    for (int i = 0; i < a.size(); ++i) {
        ans[i] = a[i];
    }
    for (int i = a.size(); i < n; ++i) {
        ans[i] = 0;
    }
    return ans;
}

cld* calcwNdegs(int n) {
    cld* wNdegs = new cld[n];
    wNdegs[0] = 1.0;
    for (int l = 2; l <= n; l *= 2) {
        ld ang = 2*PI/l;
        cld wl(cosl(ang), sinl(ang));
        for (int i = l/2 - 1; i >= 0; --i) {
            wNdegs[2*i] = wNdegs[i];
            wNdegs[2*i+1] = wNdegs[i] * wl;
        }
    }
    return wNdegs;
}

vector<long long> multipy(const vector<long long>& a, const vector<long long>& b, cld* wNdegs) {
    int n = 1;
    while (n < max(a.size(), b.size())) {
        n *= 2;
    }
    cld* ca = makeComplex(a, 2*n);
    cld* cb = makeComplex(b, 2*n);
    fft(ca, 2*n, wNdegs);
    fft(cb, 2*n, wNdegs);
    cld cc[2*n];
    for (int i = 0; i < 2*n; ++i) {
        cc[i] = ca[i] * cb[i];
    }
    vector<long long> c(2*n);
    fftInverse(cc, 2*n, wNdegs);
    for (int i = 0; i < 2*n; ++i) {
        c[i] = floorl(cc[i].real() + 0.5);
    }
    return c;

}

int main() {
    cld* wNdegs = calcwNdegs(N);
    vector<long long> a{1, 2, 3}, b{1, 1};
    vector<long long> c = multipy(a, b, wNdegs);
    for (auto cc : c) cout << cc << ' '; cout << endl;
}

