#include <bits/stdc++.h>

using namespace std;

#define int long long
#define endl '\n'


int INF = 1e18;
mt19937 rnd(179);
namespace Geometry {
    long double const eps = 0.0000001;
    long double const Pi = acosl(-1);

    template<typename T>
    struct Turn{
        // a b
        // c d
        T a = 1, b = 0, c = 1, d = 0;
        Turn() = default;
        Turn(const long double& alfa) : a(cosl(alfa)), b(-sinl(alfa)), c(sinl(alfa)), d(cosl(alfa)) {}
        Turn(const T& x, const T& y) : a(x), c(y) {}
        Turn(const T& a, const T& b, const T& c, const T& d) : a(a), b(b), c(c), d(d) {}
        Turn(const Turn& other) = default;
        Turn& operator=(const Turn& other) = default;
        Turn operator* (const Turn& other) {
            Turn ans(a * other.a + b * other.c, a * other.b + b * other.d, c * other.a + d * other.c, c * other.b + d * other.d);
            return ans;
        }
        Turn& operator*=(const Turn& other) {
            Turn ans(a * other.a + b * other.c, a * other.b + b * other.d, c * other.a + d * other.c, c * other.b + d * other.d);
            this = ans;
            return *this;
        }
    };

    template<typename T>
    struct p {
        T x = 0;
        T y = 0;

        p() = default;

        p(T x, T y) : x(x), y(y) {}
        template<typename U>
        p(const p<U>& other) : x(T(other.x)), y(T(other.y)) {}


        p& operator=(const p& other) {
            x = other.x;
            y = other.y;
            return *this;
        }

        p& operator+=(const p& other) {
            x += other.x;
            y += other.y;
            return *this;
        }

        p operator-() const {
            p cp(-x, -y);
            return cp;
        }

        p& operator-=(const p& other) {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        template<typename U>
        p& operator*=(const Turn<U>& turn) {
            T new_x = turn.a * x + turn.b * y;
            y = turn.c * x + turn.d * y;
            x = new_x;
            return *this;
        }
        p& operator*=(const auto& t) {
            x *= t;
            y *= t;
            return *this;
        }

        p& operator/=(const auto& t) {
            x /= t;
            y /= t;
            return *this;
        }

        T operator&=(const p& other) {  // скалярное умножение
            return x * other.x + y * other.y;
        }


        T operator|=(const p& other) {  // векторное умножение
            return x * other.y - y * other.x;
        }

        p operator+(const p& other) const {
            p cp(*this);
            return (cp += other);
        }

        p operator-(const p& other) const {
            p cp(*this);
            return (cp -= other);
        }

        template<typename U>
        p operator*(const Turn<U>& turn) {
            p ans(turn.a * x + turn.b * y, turn.c * x + turn.d * y);
            return ans;
        }

        p operator*(const auto& t) const {
            p cp(*this);
            return (cp *= t);
        }

        p operator/(const auto& t) const {
            p cp(*this);
            return (cp /= t);
        }

        T operator&(const p& other) const {
            return x * other.x + y * other.y;
        }

        T operator|(const p& other) const {
            return x * other.y - y * other.x;
        }

        T len2() const {
            return x * x + y * y;
        }

        long double len() const {
            return sqrtl(len2());
        }

        void pr() {
            cout << '(' << x << ", " << y << ")\n";
        }

        template<typename U>
        friend bool operator==(const p<U> &a, const p<U> &b);

        template<typename U>
        friend bool operator!=(const p<U> &a, const p<U> &b);
    };

    bool operator==(const p<long double>& a, const p<long double>& b) {
        return (abs(a.x - b.x) < eps) && (abs(a.y - b.y) < eps);
    }

    template <typename T>
    bool operator==(const p<T>& a, const p<T>& b)  {
        return (a.x == b.x) && (a.y == b.y);
    }
    bool operator!=(const p<long double>& a, const p<long double>& b) {
        return (abs(a.x - b.x) >= eps) || (abs(a.y - b.y) >= eps);
    }

    template <typename T>
    bool operator!=(const p<T>& a, const p<T>& b)  {
        return (a.x != b.x) || (a.y != b.y);
    }

    template <typename T>
    long double angle(const p<T>& a, const p<T>& b) {
        return atan2(a|b, a&b);
    }


    template<typename T>
    struct Seg{
        p<T> start;
        p<T> finish;
        Seg() = default;
        Seg(const p<T>& finish) : start(p((T)0, (T)0)), finish(finish) {};
        Seg(const p<T>& start, const p<T>& finish) : start(start), finish(finish) {};
        Seg(const Seg& other) : start(other.start), finish(other.finish) {};
        Seg& operator=(const Seg& other) {
            start = other.start;
            finish = other.finish;
            return *this;
        }
    };
    template<typename T>
    struct Ray{
        p<T> start;
        p<T> finish;
        Ray() = default;
        Ray(const p<T>& finish) : start(p((T)0, (T)0)), finish(finish) {};
        Ray(const p<T>& start, const p<T>& finish) : start(start), finish(finish) {};
        Ray(const Seg<T>& seg) : start(seg.start), finish(seg.finish) {};
        Ray(const Ray& other) : start(other.start), finish(other.finish) {};
        Ray& operator=(const Ray& other) {
            start = other.start;
            finish = other.finish;
            return *this;
        }
    };

    template<typename T>
    struct Line{
        p<T> start;
        p<T> finish;
        Line() = default;
        Line(const p<T>& finish) : start(p((T)0, (T)0)), finish(finish) {};
        Line(const p<T>& start, const p<T>& finish) : start(start), finish(finish) {};
        Line(const Seg<T>& seg) : start(seg.start), finish(seg.finish) {};
        Line(const Ray<T> ray) : start(ray.start), finish(ray.finish) {};
        Line(const Line& other) : start(other.start), finish(other.finish) {};
        Line& operator=(const Line& other) {
            start = other.start;
            finish = other.finish;
            return *this;
        }
    };

    template<typename T, typename U>
    struct Circle {
        p<T> centr;
        U rad;
        Circle() : centr(), rad(U(0)) {};
        Circle(const p<T>& centr) : centr(centr), rad(U(0)) {};
        Circle(const p<T>& centr, const U& rad): centr(centr), rad(rad) {};
        Circle(const Circle& other): centr(other.centr), rad(other.rad) {};
        Circle operator=(const Circle& other) {
            centr = other.centr;
            rad = other.rad;
            return *this;
        }
    };

    template<typename T, typename U>
    p<long double> Project(const p<T>& a, const Line<U>& line) {

        // TODO
    }

    template<typename T, typename U>
    p<long double> Project(const p<T>& a, const Ray<U>& ray) {
        return Project(a, Line(ray));
    }

    template<typename T, typename U>
    p<long double> Project(const p<T>& a, const Seg<U>& seg) {
        return Project(a, Line(seg));
    }

    template<typename T, typename U>
    bool Belong(const p<T>& a, const Line<U>& line) {
        // TODO
    }

    template<typename T, typename U>
    bool Belong(const p<T>& a, const Ray<U>& ray) {
        // TODO
    }

    template<typename T, typename U>
    bool Belong(const p<T>& a, const Seg<U>& seg) {
        // TODO
    }

    template<typename T>
    bool DoIntersect(const p<T>& a, const Line<U>& line) {
        // TODO
    }

    template<typename T, typename U>
    bool DoIntersect(const p<T>& a, const Ray<U>& ray) {
        // TODO
    }

    template<typename T, typename U>
    bool DoIntersect(const p<T>& a, const Seg<U>& seg) {
        // TODO
    }

    template<typename T, typename U>
    long double Dist(const p<T>& a, const Line<U>& line) {

    }

    template<typename T, typename U>
    long double Dist(const p<T>& a, const Ray<U>& ray) {
        // TODO
    }

    template<typename T, typename U>
    long double Dist(const p<T>& a, const Seg<U>& seg) {
        // TODO
    }
}

using namespace Geometry;

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout.precision(20);
}

