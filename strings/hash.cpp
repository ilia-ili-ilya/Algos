template<int mod>
class hstring {
private:
    // TODO можно добавить предподсчет степеней z
    static const int z = 179;
    string s;
    int n;
    vector<ll> h;
    static ll Pow(ll x, ll p) {
        if (p == 0) return 1;
        if (p % 2 == 0) return Pow((x*x) % mod, p / 2);
        return (Pow(x, p-1) * x) % mod;
    }
    static ll Anti(int x) {
        return Pow(x, mod-2);
    }
public:
    static ll GetHash(const string& s) {
        ll ans = 0;
        for (int i = 0; i < s.size(); ++i) {
            ans *= z;
            ans += s[i];
            ans %= mod;
        }
        return ans;
    }

    hstring(const string& s) : n(s.size()), h(n) {
        h[0] = s[0];
        for (int i = 1; i < n; ++i) {
            h[i] = (h[i-1] * z + s[i]) % mod;
        }
    }

    hstring(const hstring& other) : s(other.s), n(other.n), h(other.h) {}

    hstring() = default;

    hstring& operator=(hstring other) {
        swap(s, other.s);
        swap(n, other.n);
        swap(h, other.h);
        return *this;
    }

    bool operator==(const hstring& other) const {
        if (n != other.n) return false;
        return (h[n-1] == other.h[other.n - 1]);
    }

    bool operator!=(const hstring& other) const {
        if (n != other.n) return true;
        return (h[n-1] != other.h[other.n - 1]);
    }

    int GetSize() const {
        return n;
    }

    void AddChar(const char& c) {
        s += c;
        h.push_back((h[n-1] * z + s[n]) % mod);
        ++n;
    }

    void PopChar() {
        s.pop_back();
        --n;
        h.pop_back();
    }

    char& operator[] (int x) {
        return s[x];
    }

    char operator[] (int x) const {
        return s[x];
    }

    hstring& operator+(const hstring& other) {
        for (int i = 0; i < other.GetSize(); ++i) {
            AddChar(other[i]);
        }
        return *this;
    }

    ll hashlr(int l, int r) { // [l, r)
        ll ans;
        if (l != 0) ans = mod - ((h[l-1] * Pow(z, r - l)) % mod);
        else ans = 0;
        ans = (ans + h[r-1]) % mod;
        return ans;
    }
};
typedef hstring<1'000'000'007> hstr;

