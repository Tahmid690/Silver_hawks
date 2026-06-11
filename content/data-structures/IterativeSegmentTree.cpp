/**
 * Author: 
 * Date: 
 * License: 
 * Source: 
 * Description: 
 * Time: 
 * Status: 
 */
struct SegTree {
    using T = long long; 
    const T ID = 0;      
    T combine(T a, T b) { return a + b; }
    int n;
    vector<T> tree;
    SegTree(int _n) { n = _n; tree.assign(2 * n, ID); }
    void build(const vector<T>& a) {
        for (int i = 0; i < n; i++) tree[n + i] = a[i];
        for (int i = n - 1; i > 0; --i) 
            tree[i] = combine(tree[i << 1], tree[i << 1 | 1]);
    }
    void update(int p, T value) {
        for (tree[p += n] = value; p > 1; p >>= 1) {
            tree[p >> 1] = combine(tree[p], tree[p ^ 1]);
        }
    }
    T query(int l, int r) {
        T resL = ID, resR = ID;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resL = combine(resL, tree[l++]);
            if (r & 1) resR = combine(tree[--r], resR);
        }
        return combine(resL, resR);
    }
};