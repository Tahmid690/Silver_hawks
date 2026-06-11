/**
 * Author: ChatGPT
 * Date: 2025-09-27
 * License: CC0
 * Source: ChatGPT
 * Description: Linear Time CHT
 *  Useful for dynamic programming (``convex hull trick'').
 * Time: O(N) amortized
 * Status: cses-tested
 */
struct Line {
    ll k, m; 
    ll eval(ll x) const { return k * x + m; }
    long double intersectX(const Line& other) const {
        return (long double)(other.m - m) / (long double)(k - other.k);
    }
};

struct LineContainer {
    deque<Line> dq;
    void add(ll k, ll m) {
        Line nw{ k, m };
        while (dq.size() >= 2) {
            Line l1 = dq[dq.size()-2];
            Line l2 = dq[dq.size()-1];
            long double x12 = l1.intersectX(l2);
            long double x23 = l2.intersectX(nw);
            if (x12 >= x23) dq.pop_back();
            else break;
        }
        dq.push_back(nw);
    }
    ll query(ll x) {
        assert(!dq.empty());
        while (dq.size() >= 2 && dq[0].eval(x) <= dq[1].eval(x)) dq.pop_front();
        return dq.front().eval(x);
    }

    bool empty() const { return dq.empty(); }
};
