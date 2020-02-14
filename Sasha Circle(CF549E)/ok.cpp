#include <bits/stdc++.h>
 
using namespace std;
 
typedef long double ld;
 
const ld EPS = 1e-14;
const ld INF = 1e18;
 
struct Point {
    int x, y;
    Point();
    Point(int x, int y);
    bool operator==(const Point &rhs) const;
    Point operator-(const Point &rhs) const;
    int cross(const Point &rhs) const;
    int dot(const Point &rhs) const;
};
 
ld sqr(ld x);
ld dis(const Point &a, const Point &b);
int cos(const Point &a, const Point &b, const Point &c);
int sin(const Point &a, const Point &b, const Point &c);
 
int N, M;
bool ans;
 
vector<Point> convex_hull(const vector<Point> &_A) {
    vector<Point> A = _A;
    Point base = A[0];
    for (Point i : A)
        if (i.x < base.x || i.x == base.x && i.y < base.y) base = i;
    sort(A.begin(), A.end(), [&base](const Point &a, const Point &b){
                                 if (a == base ^ b == base) return a == base;
                                 int t = (a - base).cross(b - base);
                                 if (t != 0) return t > 0;
                                 return dis(a, base) < dis(b, base);
                             });
    vector<Point> res;
    for (Point i : A) {
        while (res.size() >= 2 && (i - res.end()[-2]).cross(res.end()[-1] - res.end()[-2]) >= 0)
            res.pop_back();
        res.push_back(i);
    }
    while (res.size() > 2 && (res.end()[-1] - base).cross(res.end()[-2] - base) == 0) {
        res.pop_back();
    }
    return res;
}
 
void check(Point u, Point v, const vector<Point> &A, const vector<Point> &B) {
    if (ans) return;
    ld cot_l = -INF, cot_r = INF; // inscribed angle to the right of uv
    bool strict = false;
    for (Point i : B) {
        ld c = cos(u, v, i), s = sin(u, v, i);
        if (s == 0) {
            if (c < 0) return;
            continue;
        }
        ld cot = ld(c) / s;
        if (s > 0 && cot < cot_r) strict = true, cot_r = cot;
        if (s < 0 && cot > cot_l) strict = true, cot_l = cot;
        if (cot_r - cot_l < (strict ? EPS : -EPS)) return;
    }
    for (Point i : A) {
        if (i == u || i == v) continue;
        int c = cos(u, v, i), s = sin(u, v, i);
        if (s == 0) continue;
        ld cot = ld(c) / s;
        if (s > 0) cot_l = max(cot_l, cot);
        if (s < 0) cot_r = min(cot_r, cot);
        if (cot_r - cot_l < (strict ? EPS : -EPS)) return;
    }
    if (cot_r - cot_l > (strict ? EPS : -EPS)) ans = true;
}
 
void partition(const vector<Point> &hull, int l, int r, const vector<Point> &A, const vector<Point> &B) {
    check(hull[l], hull[r], hull, B);
    if (r - l <= 1) return;
 
    Point u = hull[l], v = hull[r];
    ld cot_max = -INF; int max_pos;
    for (int i = l + 1; i < r; i++) {
        ld t = ld(cos(v, u, hull[i])) / sin(v, u, hull[i]);
        if (t > cot_max) {
            cot_max = t;
            max_pos = i;
        }
    }
    partition(hull, l, max_pos, A, B);
    partition(hull, max_pos, r, A, B);
}
 
void solve(const vector<Point> &A, const vector<Point> &B) {
    if (A.size() == 1) {
        ans = true;
        return;
    }
    vector<Point> hullA = convex_hull(A);
    partition(hullA, 0, hullA.size() - 1, A, B);
}
 
int main() {
    scanf("%d%d", &N, &M);
    vector<Point> A, B;
    for (int i = 1; i <= N; i++) {
        int x, y; scanf("%d%d", &x, &y);
        A.emplace_back(x, y);
    }
    for (int i = 1; i <= M; i++) {
        int x, y; scanf("%d%d", &x, &y);
        B.emplace_back(x, y);
    }
    solve(A, B);
    solve(B, A);
    printf(ans ? "YES\n" : "NO\n");
}
 
Point::Point() {}
Point::Point(int x, int y) : x(x), y(y) {}
bool Point::operator==(const Point &rhs) const { return x == rhs.x && y == rhs.y; }
Point Point::operator-(const Point &rhs) const { return Point(x - rhs.x, y - rhs.y); }
int Point::cross(const Point &rhs) const { return x * rhs.y - rhs.x * y; }
int Point::dot(const Point &rhs) const { return x * rhs.x + y * rhs.y; }
 
ld sqr(ld x) { return x * x; }
ld dis(const Point &a, const Point &b) { return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y)); }
 
int sin(const Point &a, const Point &b, const Point &c) {
    return (a - c).cross(b - c);
}
 
int cos(const Point &a, const Point &b, const Point &c) {
    return (a - c).dot(b - c);
}