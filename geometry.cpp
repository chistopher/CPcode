
#include "cmath"

struct Point {
    double x,y;
    Point operator*(double t) { return {x*t, y*t}; }
    Point operator+(Point other) { return {x+other.x, y+other.y}; }
    Point operator-(Point other) { return {x-other.x, y-other.y}; }
};
auto dot(Point a, Point b) { return a.x*b.x + a.y*b.y; }
auto cross(Point a, Point b) { return a.x*b.y - a.y*b.x; }
auto abs(Point a) { return sqrt(dot(a,a)); }
auto proj(Point a, Point b) { return dot(a,b) / abs(b); }
auto distPointLine(Point a, Point s, Point d) { return fabs(cross(d,a-s) / abs(d)); }
auto lineIntersection(Point s1, Point d1, Point s2, Point d2) { return s1 + d1 * (cross(d2,s2-s1) / cross(d1,d2)); } // assumes lines not parallel
