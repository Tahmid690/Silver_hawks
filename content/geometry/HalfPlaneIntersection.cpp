/**
 * Author: 
 * Date: 
 * License: CC0
 * Source: 
 * Description: 
 * Status: tested
 */
#ifndef HALFPLANE_H
#define HALFPLANE_H
// Ensure 'eps' is defined in your main template or uncomment below:
// const double eps = 1e-12;
// Structure to represent a Half-Plane
// The valid region is to the LEFT of the vector (a -> b)
struct HP {
    P a, b;
    HP() {}
    HP(P a, P b) : a(a), b(b) {}
    HP(const HP& rhs) : a(rhs.a), b(rhs.b) {}
 
    int operator < (const HP& rhs) const {
        P p = b - a;
        P q = rhs.b - rhs.a;
        int fp = (p.y < 0 || (p.y == 0 && p.x < 0));
        int fq = (q.y < 0 || (q.y == 0 && q.x < 0));
        if (fp != fq) return fp == 0;
        if (p.cross(q)) return p.cross(q) > 0;
        return p.cross(rhs.b - a) < 0;
    }
 
    P line_line_intersection(P a, P b, P c, P d) {
        b = b - a; d = c - d; c = c - a;
        return a + b * c.cross(d) / b.cross(d);
    }
 
    P intersection(const HP &v) {
        return line_line_intersection(a, b, v.a, v.b);
    }
};
 
// Check if the intersection of lines b and c lies inside half-plane a
bool check(HP a, HP b, HP c) {
    return (a.b - a.a).cross(b.intersection(c) - a.a) > -eps;
}
 
// Returns the vertices of the convex polygon formed by the intersection
// of the given half-planes. Vertices are returned in CCW order.
// Complexity: O(N log N)
vector<P> half_plane_intersection(vector<HP> h) {
    sort(h.begin(), h.end());
    vector<HP> tmp;
    for (int i = 0; i < h.size(); i++) {
        if (!i || (h[i].b - h[i].a).cross(h[i - 1].b - h[i - 1].a)) {
            tmp.push_back(h[i]);
        }
    }
    h = tmp;
    vector<HP> q(h.size() + 10);
    int qh = 0, qe = 0;
    for (int i = 0; i < h.size(); i++) {
        while (qe - qh > 1 && !check(h[i], q[qe - 2], q[qe - 1])) qe--;
        while (qe - qh > 1 && !check(h[i], q[qh], q[qh + 1])) qh++;
        q[qe++] = h[i];
    }
    while (qe - qh > 2 && !check(q[qh], q[qe - 2], q[qe - 1])) qe--;
    while (qe - qh > 2 && !check(q[qe - 1], q[qh], q[qh + 1])) qh++;
    
    vector<HP> res;
    for (int i = qh; i < qe; i++) res.push_back(q[i]);
    
    vector<P> hull;
    if (res.size() > 2) {
        for (int i = 0; i < res.size(); i++) {
             hull.push_back(res[i].intersection(res[(i + 1) % ((int)res.size())]));
        }
    }
    return hull;
}
 
#endif
