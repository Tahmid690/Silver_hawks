/**
 * Author: 
 * Date: 
 * License: 
 * Source: 
 * Description: 
 * Time: 
 * Status: 
 */
const int LOGN = 20;
int tin[N], tout[N], depth[N];
int up[N][LOGN];
int timer;

void dfs_lca(int u, int p, int d) {
    depth[u] = d;
    tin[u] = ++timer;
    up[u][0] = p;
    for (int i = 1; i < LOGN; i++) {
        up[u][i] = up[up[u][i - 1]][i - 1];
    }
    for (int v : g[u]) {
        if (v != p) dfs_lca(v, u, d + 1);
    }
    tout[u] = timer;
}
bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}
int get_lca(int u, int v) {
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;
    for (int i = LOGN - 1; i >= 0; i--) {
        if (!is_ancestor(up[u][i], v)) {
            u = up[u][i];
        }
    }
    return up[u][0];
}
int get_kth_ancestor(int node, int k) {
    for (int i = 0; i < LOGN; i++) {
        if ((k >> i) & 1) {
            node = up[node][i];
        }
    }
    return node;
}